// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2007 Julien Pommier
// Copyright (C) 2014 Pedro Gonnet (pedro.gonnet@gmail.com)
// Copyright (C) 2009-2019 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

/* The exp and log functions of this file initially come from
 * Julien Pommier's sse math library: http://gruntthepeon.free.fr/ssemath/
 */

#ifndef EIGEN_ARCH_GENERIC_PACKET_MATH_FUNCTIONS_H
#define EIGEN_ARCH_GENERIC_PACKET_MATH_FUNCTIONS_H

namespace Eigen {
namespace internal {

template<typename Packet, int N> EIGEN_DEVICE_FUNC inline Packet
pset(const typename unpacket_traits<Packet>::type (&a)[N] /* a */) {
  EIGEN_STATIC_ASSERT(unpacket_traits<Packet>::size == N, THE_ARRAY_SIZE_SHOULD_EQUAL_WITH_PACKET_SIZE);
  return pload<Packet>(a);
}

template<typename Packet> EIGEN_STRONG_INLINE Packet
pfrexp_float(const Packet& a, Packet& exponent) {
  typedef typename unpacket_traits<Packet>::integer_packet PacketI;
  const Packet cst_126f = pset1<Packet>(126.0f);
  const Packet cst_half = pset1<Packet>(0.5f);
  const Packet cst_inv_mant_mask  = pset1frombits<Packet>(~0x7f800000u);
  exponent = psub(pcast<PacketI,Packet>(plogical_shift_right<23>(preinterpret<PacketI>(a))), cst_126f);
  return por(pand(a, cst_inv_mant_mask), cst_half);
}

template<typename Packet> EIGEN_STRONG_INLINE Packet
pfrexp_double(const Packet& a, Packet& exponent) {
  typedef typename unpacket_traits<Packet>::integer_packet PacketI;
  const Packet cst_1022d = pset1<Packet>(1022.0);
  const Packet cst_half = pset1<Packet>(0.5);
  const Packet cst_inv_mant_mask  = pset1frombits<Packet>(static_cast<uint64_t>(~0x7ff0000000000000ull));
  exponent = psub(pcast<PacketI,Packet>(plogical_shift_right<52>(preinterpret<PacketI>(a))), cst_1022d);
  return por(pand(a, cst_inv_mant_mask), cst_half);
}

template<typename Packet> EIGEN_STRONG_INLINE Packet
pldexp_float(Packet a, Packet exponent)
{
  typedef typename unpacket_traits<Packet>::integer_packet PacketI;
  const Packet cst_127 = pset1<Packet>(127.f);
  // return a * 2^exponent
  PacketI ei = pcast<Packet,PacketI>(padd(exponent, cst_127));
  return pmul(a, preinterpret<Packet>(plogical_shift_left<23>(ei)));
}

template<typename Packet> EIGEN_STRONG_INLINE Packet
pldexp_double(Packet a, Packet exponent)
{
  typedef typename unpacket_traits<Packet>::integer_packet PacketI;
  const Packet cst_1023 = pset1<Packet>(1023.0);
  // return a * 2^exponent
  PacketI ei = pcast<Packet,PacketI>(padd(exponent, cst_1023));
  return pmul(a, preinterpret<Packet>(plogical_shift_left<52>(ei)));
}

// Natural or base 2 logarithm.
// Computes log(x) as log(2^e * m) = C*e + log(m), where the constant C =log(2)
// and m is in the range [sqrt(1/2),sqrt(2)). In this range, the logarithm can
// be easily approximated by a polynomial centered on m=1 for stability.
// TODO(gonnet): Further reduce the interval allowing for lower-degree
//               polynomial interpolants -> ... -> profit!
template <typename Packet, bool base2>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog_impl_float(const Packet _x)
{
  Packet x = _x;

  const Packet cst_1              = pset1<Packet>(1.0f);
  const Packet cst_neg_half       = pset1<Packet>(-0.5f);
  // The smallest non denormalized float number.
  const Packet cst_min_norm_pos   = pset1frombits<Packet>( 0x00800000u);
  const Packet cst_minus_inf      = pset1frombits<Packet>( 0xff800000u);
  const Packet cst_pos_inf        = pset1frombits<Packet>( 0x7f800000u);

  // Polynomial coefficients.
  const Packet cst_cephes_SQRTHF = pset1<Packet>(0.707106781186547524f);
  const Packet cst_cephes_log_p0 = pset1<Packet>(7.0376836292E-2f);
  const Packet cst_cephes_log_p1 = pset1<Packet>(-1.1514610310E-1f);
  const Packet cst_cephes_log_p2 = pset1<Packet>(1.1676998740E-1f);
  const Packet cst_cephes_log_p3 = pset1<Packet>(-1.2420140846E-1f);
  const Packet cst_cephes_log_p4 = pset1<Packet>(+1.4249322787E-1f);
  const Packet cst_cephes_log_p5 = pset1<Packet>(-1.6668057665E-1f);
  const Packet cst_cephes_log_p6 = pset1<Packet>(+2.0000714765E-1f);
  const Packet cst_cephes_log_p7 = pset1<Packet>(-2.4999993993E-1f);
  const Packet cst_cephes_log_p8 = pset1<Packet>(+3.3333331174E-1f);

  // Truncate input values to the minimum positive normal.
  x = pmax(x, cst_min_norm_pos);

  Packet e;
  // extract significant in the range [0.5,1) and exponent
  x = pfrexp(x,e);

  // part2: Shift the inputs from the range [0.5,1) to [sqrt(1/2),sqrt(2))
  // and shift by -1. The values are then centered around 0, which improves
  // the stability of the polynomial evaluation.
  //   if( x < SQRTHF ) {
  //     e -= 1;
  //     x = x + x - 1.0;
  //   } else { x = x - 1.0; }
  Packet mask = pcmp_lt(x, cst_cephes_SQRTHF);
  Packet tmp = pand(x, mask);
  x = psub(x, cst_1);
  e = psub(e, pand(cst_1, mask));
  x = padd(x, tmp);

  Packet x2 = pmul(x, x);
  Packet x3 = pmul(x2, x);

  // Evaluate the polynomial approximant of degree 8 in three parts, probably
  // to improve instruction-level parallelism.
  Packet y, y1, y2;
  y  = pmadd(cst_cephes_log_p0, x, cst_cephes_log_p1);
  y1 = pmadd(cst_cephes_log_p3, x, cst_cephes_log_p4);
  y2 = pmadd(cst_cephes_log_p6, x, cst_cephes_log_p7);
  y  = pmadd(y, x, cst_cephes_log_p2);
  y1 = pmadd(y1, x, cst_cephes_log_p5);
  y2 = pmadd(y2, x, cst_cephes_log_p8);
  y  = pmadd(y, x3, y1);
  y  = pmadd(y, x3, y2);
  y  = pmul(y, x3);

  y = pmadd(cst_neg_half, x2, y);
  x = padd(x, y);

  // Add the logarithm of the exponent back to the result of the interpolation.
  if (base2) {
    const Packet cst_log2e = pset1<Packet>(static_cast<float>(EIGEN_LOG2E));
    x = pmadd(x, cst_log2e, e);
  } else {
    const Packet cst_ln2 = pset1<Packet>(static_cast<float>(EIGEN_LN2));
    x = pmadd(e, cst_ln2, x);
  }

  Packet invalid_mask = pcmp_lt_or_nan(_x, pzero(_x));
  Packet iszero_mask  = pcmp_eq(_x,pzero(_x));
  Packet pos_inf_mask = pcmp_eq(_x,cst_pos_inf);
  // Filter out invalid inputs, i.e.:
  //  - negative arg will be NAN
  //  - 0 will be -INF
  //  - +INF will be +INF
  return pselect(iszero_mask, cst_minus_inf,
                              por(pselect(pos_inf_mask,cst_pos_inf,x), invalid_mask));
}

template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog_float(const Packet _x)
{
  return plog_impl_float<Packet, /* base2 */ false>(_x);
}

template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog2_float(const Packet _x)
{
  return plog_impl_float<Packet, /* base2 */ true>(_x);
}

/* Returns the base e (2.718...) or base 2 logarithm of x.
 * The argument is separated into its exponent and fractional parts.
 * The logarithm of the fraction in the interval [sqrt(1/2), sqrt(2)],
 * is approximated by
 *
 *     log(1+x) = x - 0.5 x**2 + x**3 P(x)/Q(x).
 *
 * for more detail see: http://www.netlib.org/cephes/
 */
template <typename Packet, bool base2>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog_impl_double(const Packet _x)
{
  Packet x = _x;

  const Packet cst_1              = pset1<Packet>(1.0);
  const Packet cst_neg_half       = pset1<Packet>(-0.5);
  // The smallest non denormalized double.
  const Packet cst_min_norm_pos   = pset1frombits<Packet>( static_cast<uint64_t>(0x0010000000000000ull));
  const Packet cst_minus_inf      = pset1frombits<Packet>( static_cast<uint64_t>(0xfff0000000000000ull));
  const Packet cst_pos_inf        = pset1frombits<Packet>( static_cast<uint64_t>(0x7ff0000000000000ull));


 // Polynomial Coefficients for log(1+x) = x - x**2/2 + x**3 P(x)/Q(x)
 //                             1/sqrt(2) <= x < sqrt(2)
  const Packet cst_cephes_SQRTHF = pset1<Packet>(0.70710678118654752440E0);
  const Packet cst_cephes_log_p0 = pset1<Packet>(1.01875663804580931796E-4);
  const Packet cst_cephes_log_p1 = pset1<Packet>(4.97494994976747001425E-1);
  const Packet cst_cephes_log_p2 = pset1<Packet>(4.70579119878881725854E0);
  const Packet cst_cephes_log_p3 = pset1<Packet>(1.44989225341610930846E1);
  const Packet cst_cephes_log_p4 = pset1<Packet>(1.79368678507819816313E1);
  const Packet cst_cephes_log_p5 = pset1<Packet>(7.70838733755885391666E0);

  const Packet cst_cephes_log_q0 = pset1<Packet>(1.0);
  const Packet cst_cephes_log_q1 = pset1<Packet>(1.12873587189167450590E1);
  const Packet cst_cephes_log_q2 = pset1<Packet>(4.52279145837532221105E1);
  const Packet cst_cephes_log_q3 = pset1<Packet>(8.29875266912776603211E1);
  const Packet cst_cephes_log_q4 = pset1<Packet>(7.11544750618563894466E1);
  const Packet cst_cephes_log_q5 = pset1<Packet>(2.31251620126765340583E1);

  // Truncate input values to the minimum positive normal.
  x = pmax(x, cst_min_norm_pos);

  Packet e;
  // extract significant in the range [0.5,1) and exponent
  x = pfrexp(x,e);
  
  // Shift the inputs from the range [0.5,1) to [sqrt(1/2),sqrt(2))
  // and shift by -1. The values are then centered around 0, which improves
  // the stability of the polynomial evaluation.
  //   if( x < SQRTHF ) {
  //     e -= 1;
  //     x = x + x - 1.0;
  //   } else { x = x - 1.0; }
  Packet mask = pcmp_lt(x, cst_cephes_SQRTHF);
  Packet tmp = pand(x, mask);
  x = psub(x, cst_1);
  e = psub(e, pand(cst_1, mask));
  x = padd(x, tmp);

  Packet x2 = pmul(x, x);
  Packet x3 = pmul(x2, x);

  // Evaluate the polynomial approximant , probably to improve instruction-level parallelism.
  // y = x - 0.5*x^2 + x^3 * polevl( x, P, 5 ) / p1evl( x, Q, 5 ) );
  Packet y, y1, y_;
  y  = pmadd(cst_cephes_log_p0, x, cst_cephes_log_p1);
  y1 = pmadd(cst_cephes_log_p3, x, cst_cephes_log_p4);
  y  = pmadd(y, x, cst_cephes_log_p2);
  y1 = pmadd(y1, x, cst_cephes_log_p5);
  y_ = pmadd(y, x3, y1);

  y  = pmadd(cst_cephes_log_q0, x, cst_cephes_log_q1);
  y1 = pmadd(cst_cephes_log_q3, x, cst_cephes_log_q4);
  y  = pmadd(y, x, cst_cephes_log_q2);
  y1 = pmadd(y1, x, cst_cephes_log_q5);
  y  = pmadd(y, x3, y1);

  y_ = pmul(y_, x3);
  y  = pdiv(y_, y);

  y = pmadd(cst_neg_half, x2, y);
  x = padd(x, y);

  // Add the logarithm of the exponent back to the result of the interpolation.
  if (base2) {
    const Packet cst_log2e = pset1<Packet>(static_cast<double>(EIGEN_LOG2E));
    x = pmadd(x, cst_log2e, e);
  } else {
    const Packet cst_ln2 = pset1<Packet>(static_cast<double>(EIGEN_LN2));
    x = pmadd(e, cst_ln2, x);
  }

  Packet invalid_mask = pcmp_lt_or_nan(_x, pzero(_x));
  Packet iszero_mask  = pcmp_eq(_x,pzero(_x));
  Packet pos_inf_mask = pcmp_eq(_x,cst_pos_inf);
  // Filter out invalid inputs, i.e.:
  //  - negative arg will be NAN
  //  - 0 will be -INF
  //  - +INF will be +INF
  return pselect(iszero_mask, cst_minus_inf,
                              por(pselect(pos_inf_mask,cst_pos_inf,x), invalid_mask));
}

template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog_double(const Packet _x)
{
  return plog_impl_double<Packet, /* base2 */ false>(_x);
}

template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet plog2_double(const Packet _x)
{
  return plog_impl_double<Packet, /* base2 */ true>(_x);
}

/** \internal \returns log(1 + x) computed using W. Kahan's formula.
    See: http://www.plunk.org/~hatch/rightway.php
 */
template<typename Packet>
Packet generic_plog1p(const Packet& x)
{
  typedef typename unpacket_traits<Packet>::type ScalarType;
  const Packet one = pset1<Packet>(ScalarType(1));
  Packet xp1 = padd(x, one);
  Packet small_mask = pcmp_eq(xp1, one);
  Packet log1 = plog(xp1);
  Packet inf_mask = pcmp_eq(xp1, log1);
  Packet log_large = pmul(x, pdiv(log1, psub(xp1, one)));
  return pselect(por(small_mask, inf_mask), x, log_large);
}

/** \internal \returns exp(x)-1 computed using W. Kahan's formula.
    See: http://www.plunk.org/~hatch/rightway.php
 */
template<typename Packet>
Packet generic_expm1(const Packet& x)
{
  typedef typename unpacket_traits<Packet>::type ScalarType;
  const Packet one = pset1<Packet>(ScalarType(1));
  const Packet neg_one = pset1<Packet>(ScalarType(-1));
  Packet u = pexp(x);
  Packet one_mask = pcmp_eq(u, one);
  Packet u_minus_one = psub(u, one);
  Packet neg_one_mask = pcmp_eq(u_minus_one, neg_one);
  Packet logu = plog(u);
  // The following comparison is to catch the case where
  // exp(x) = +inf. It is written in this way to avoid having
  // to form the constant +inf, which depends on the packet
  // type.
  Packet pos_inf_mask = pcmp_eq(logu, u);
  Packet expm1 = pmul(u_minus_one, pdiv(x, logu));
  expm1 = pselect(pos_inf_mask, u, expm1);
  return pselect(one_mask,
                 x,
                 pselect(neg_one_mask,
                         neg_one,
                         expm1));
}


// Exponential function. Works by writing "x = m*log(2) + r" where
// "m = floor(x/log(2)+1/2)" and "r" is the remainder. The result is then
// "exp(x) = 2^m*exp(r)" where exp(r) is in the range [-1,1).
template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet pexp_float(const Packet _x)
{
  const Packet cst_1      = pset1<Packet>(1.0f);
  const Packet cst_half   = pset1<Packet>(0.5f);
  const Packet cst_exp_hi = pset1<Packet>( 88.3762626647950f);
  const Packet cst_exp_lo = pset1<Packet>(-88.3762626647949f);

  const Packet cst_cephes_LOG2EF = pset1<Packet>(1.44269504088896341f);
  const Packet cst_cephes_exp_p0 = pset1<Packet>(1.9875691500E-4f);
  const Packet cst_cephes_exp_p1 = pset1<Packet>(1.3981999507E-3f);
  const Packet cst_cephes_exp_p2 = pset1<Packet>(8.3334519073E-3f);
  const Packet cst_cephes_exp_p3 = pset1<Packet>(4.1665795894E-2f);
  const Packet cst_cephes_exp_p4 = pset1<Packet>(1.6666665459E-1f);
  const Packet cst_cephes_exp_p5 = pset1<Packet>(5.0000001201E-1f);

  // Clamp x.
  Packet x = pmax(pmin(_x, cst_exp_hi), cst_exp_lo);

  // Express exp(x) as exp(m*ln(2) + r), start by extracting
  // m = floor(x/ln(2) + 0.5).
  Packet m = pfloor(pmadd(x, cst_cephes_LOG2EF, cst_half));

  // Get r = x - m*ln(2). If no FMA instructions are available, m*ln(2) is
  // subtracted out in two parts, m*C1+m*C2 = m*ln(2), to avoid accumulating
  // truncation errors.
  Packet r;
#ifdef EIGEN_HAS_SINGLE_INSTRUCTION_MADD
  const Packet cst_nln2 = pset1<Packet>(-0.6931471805599453f);
  r = pmadd(m, cst_nln2, x);
#else
  const Packet cst_cephes_exp_C1 = pset1<Packet>(0.693359375f);
  const Packet cst_cephes_exp_C2 = pset1<Packet>(-2.12194440e-4f);
  r = psub(x, pmul(m, cst_cephes_exp_C1));
  r = psub(r, pmul(m, cst_cephes_exp_C2));
#endif

  Packet r2 = pmul(r, r);
  Packet r3 = pmul(r2, r);

  // Evaluate the polynomial approximant,improved by instruction-level parallelism.
  Packet y, y1, y2;
  y  = pmadd(cst_cephes_exp_p0, r, cst_cephes_exp_p1);
  y1 = pmadd(cst_cephes_exp_p3, r, cst_cephes_exp_p4);
  y2 = padd(r, cst_1);
  y  = pmadd(y, r, cst_cephes_exp_p2);
  y1 = pmadd(y1, r, cst_cephes_exp_p5);
  y  = pmadd(y, r3, y1);
  y  = pmadd(y, r2, y2);
  
  // Return 2^m * exp(r).
  return pmax(pldexp(y,m), _x);
}

template <typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet pexp_double(const Packet _x)
{
  Packet x = _x;

  const Packet cst_1 = pset1<Packet>(1.0);
  const Packet cst_2 = pset1<Packet>(2.0);
  const Packet cst_half = pset1<Packet>(0.5);

  const Packet cst_exp_hi = pset1<Packet>(709.437);
  const Packet cst_exp_lo = pset1<Packet>(-709.436139303);

  const Packet cst_cephes_LOG2EF = pset1<Packet>(1.4426950408889634073599);
  const Packet cst_cephes_exp_p0 = pset1<Packet>(1.26177193074810590878e-4);
  const Packet cst_cephes_exp_p1 = pset1<Packet>(3.02994407707441961300e-2);
  const Packet cst_cephes_exp_p2 = pset1<Packet>(9.99999999999999999910e-1);
  const Packet cst_cephes_exp_q0 = pset1<Packet>(3.00198505138664455042e-6);
  const Packet cst_cephes_exp_q1 = pset1<Packet>(2.52448340349684104192e-3);
  const Packet cst_cephes_exp_q2 = pset1<Packet>(2.27265548208155028766e-1);
  const Packet cst_cephes_exp_q3 = pset1<Packet>(2.00000000000000000009e0);
  const Packet cst_cephes_exp_C1 = pset1<Packet>(0.693145751953125);
  const Packet cst_cephes_exp_C2 = pset1<Packet>(1.42860682030941723212e-6);

  Packet tmp, fx;

  // clamp x
  x = pmax(pmin(x, cst_exp_hi), cst_exp_lo);
  // Express exp(x) as exp(g + n*log(2)).
  fx = pmadd(cst_cephes_LOG2EF, x, cst_half);

  // Get the integer modulus of log(2), i.e. the "n" described above.
  fx = pfloor(fx);

  // Get the remainder modulo log(2), i.e. the "g" described above. Subtract
  // n*log(2) out in two steps, i.e. n*C1 + n*C2, C1+C2=log2 to get the last
  // digits right.
  tmp = pmul(fx, cst_cephes_exp_C1);
  Packet z = pmul(fx, cst_cephes_exp_C2);
  x = psub(x, tmp);
  x = psub(x, z);

  Packet x2 = pmul(x, x);

  // Evaluate the numerator polynomial of the rational interpolant.
  Packet px = cst_cephes_exp_p0;
  px = pmadd(px, x2, cst_cephes_exp_p1);
  px = pmadd(px, x2, cst_cephes_exp_p2);
  px = pmul(px, x);

  // Evaluate the denominator polynomial of the rational interpolant.
  Packet qx = cst_cephes_exp_q0;
  qx = pmadd(qx, x2, cst_cephes_exp_q1);
  qx = pmadd(qx, x2, cst_cephes_exp_q2);
  qx = pmadd(qx, x2, cst_cephes_exp_q3);

  // I don't really get this bit, copied from the SSE2 routines, so...
  // TODO(gonnet): Figure out what is going on here, perhaps find a better
  // rational interpolant?
  x = pdiv(px, psub(qx, px));
  x = pmadd(cst_2, x, cst_1);

  // Construct the result 2^n * exp(g) = e * x. The max is used to catch
  // non-finite values in the input.
  return pmax(pldexp(x,fx), _x);
}

// The following code is inspired by the following stack-overflow answer:
//   https://stackoverflow.com/questions/30463616/payne-hanek-algorithm-implementation-in-c/30465751#30465751
// It has been largely optimized:
//  - By-pass calls to frexp.
//  - Aligned loads of required 96 bits of 2/pi. This is accomplished by
//    (1) balancing the mantissa and exponent to the required bits of 2/pi are
//    aligned on 8-bits, and (2) replicating the storage of the bits of 2/pi.
//  - Avoid a branch in rounding and extraction of the remaining fractional part.
// Overall, I measured a speed up higher than x2 on x86-64.
inline float trig_reduce_huge (float xf, int *quadrant)
{
  using Eigen::numext::int32_t;
  using Eigen::numext::uint32_t;
  using Eigen::numext::int64_t;
  using Eigen::numext::uint64_t;

  const double pio2_62 = 3.4061215800865545e-19;    // pi/2 * 2^-62
  const uint64_t zero_dot_five = uint64_t(1) << 61; // 0.5 in 2.62-bit fixed-point foramt

  // 192 bits of 2/pi for Payne-Hanek reduction
  // Bits are introduced by packet of 8 to enable aligned reads.
  static const uint32_t two_over_pi [] = 
  {
    0x00000028, 0x000028be, 0x0028be60, 0x28be60db,
    0xbe60db93, 0x60db9391, 0xdb939105, 0x9391054a,
    0x91054a7f, 0x054a7f09, 0x4a7f09d5, 0x7f09d5f4,
    0x09d5f47d, 0xd5f47d4d, 0xf47d4d37, 0x7d4d3770,
    0x4d377036, 0x377036d8, 0x7036d8a5, 0x36d8a566,
    0xd8a5664f, 0xa5664f10, 0x664f10e4, 0x4f10e410,
    0x10e41000, 0xe4100000
  };
  
  uint32_t xi = numext::bit_cast<uint32_t>(xf);
  // Below, -118 = -126 + 8.
  //   -126 is to get the exponent,
  //   +8 is to enable alignment of 2/pi's bits on 8 bits.
  // This is possible because the fractional part of x as only 24 meaningful bits.
  uint32_t e = (xi >> 23) - 118;
  // Extract the mantissa and shift it to align it wrt the exponent
  xi = ((xi & 0x007fffffu)| 0x00800000u) << (e & 0x7);

  uint32_t i = e >> 3;
  uint32_t twoopi_1  = two_over_pi[i-1];
  uint32_t twoopi_2  = two_over_pi[i+3];
  uint32_t twoopi_3  = two_over_pi[i+7];

  // Compute x * 2/pi in 2.62-bit fixed-point format.
  uint64_t p;
  p = uint64_t(xi) * twoopi_3;
  p = uint64_t(xi) * twoopi_2 + (p >> 32);
  p = (uint64_t(xi * twoopi_1) << 32) + p;

  // Round to nearest: add 0.5 and extract integral part.
  uint64_t q = (p + zero_dot_five) >> 62;
  *quadrant = int(q);
  // Now it remains to compute "r = x - q*pi/2" with high accuracy,
  // since we have p=x/(pi/2) with high accuracy, we can more efficiently compute r as:
  //   r = (p-q)*pi/2,
  // where the product can be be carried out with sufficient accuracy using double precision.
  p -= q<<62;
  return float(double(int64_t(p)) * pio2_62);
}

template<bool ComputeSine,typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
#if EIGEN_GNUC_AT_LEAST(4,4) && EIGEN_COMP_GNUC_STRICT
__attribute__((optimize("-fno-unsafe-math-optimizations")))
#endif
Packet psincos_float(const Packet& _x)
{
// Workaround -ffast-math aggressive optimizations
// See bug 1674
#if EIGEN_COMP_CLANG && defined(EIGEN_VECTORIZE_SSE)
#define EIGEN_SINCOS_DONT_OPT(X) __asm__  ("" : "+x" (X));
#else
#define EIGEN_SINCOS_DONT_OPT(X)
#endif

  typedef typename unpacket_traits<Packet>::integer_packet PacketI;

  const Packet  cst_2oPI            = pset1<Packet>(0.636619746685028076171875f); // 2/PI
  const Packet  cst_rounding_magic  = pset1<Packet>(12582912); // 2^23 for rounding
  const PacketI csti_1              = pset1<PacketI>(1);
  const Packet  cst_sign_mask       = pset1frombits<Packet>(0x80000000u);

  Packet x = pabs(_x);

  // Scale x by 2/Pi to find x's octant.
  Packet y = pmul(x, cst_2oPI);

  // Rounding trick:
  Packet y_round = padd(y, cst_rounding_magic);
  EIGEN_SINCOS_DONT_OPT(y_round)
  PacketI y_int = preinterpret<PacketI>(y_round); // last 23 digits represent integer (if abs(x)<2^24)
  y = psub(y_round, cst_rounding_magic); // nearest integer to x*4/pi

  // Reduce x by y octants to get: -Pi/4 <= x <= +Pi/4
  // using "Extended precision modular arithmetic"
  #if defined(EIGEN_HAS_SINGLE_INSTRUCTION_MADD)
  // This version requires true FMA for high accuracy
  // It provides a max error of 1ULP up to (with absolute_error < 5.9605e-08):
  const float huge_th = ComputeSine ? 117435.992f : 71476.0625f;
  x = pmadd(y, pset1<Packet>(-1.57079601287841796875f), x);
  x = pmadd(y, pset1<Packet>(-3.1391647326017846353352069854736328125e-07f), x);
  x = pmadd(y, pset1<Packet>(-5.390302529957764765544681040410068817436695098876953125e-15f), x);
  #else
  // Without true FMA, the previous set of coefficients maintain 1ULP accuracy
  // up to x<15.7 (for sin), but accuracy is immediately lost for x>15.7.
  // We thus use one more iteration to maintain 2ULPs up to reasonably large inputs.

  // The following set of coefficients maintain 1ULP up to 9.43 and 14.16 for sin and cos respectively.
  // and 2 ULP up to:
  const float huge_th = ComputeSine ? 25966.f : 18838.f;
  x = pmadd(y, pset1<Packet>(-1.5703125), x); // = 0xbfc90000
  EIGEN_SINCOS_DONT_OPT(x)
  x = pmadd(y, pset1<Packet>(-0.000483989715576171875), x); // = 0xb9fdc000
  EIGEN_SINCOS_DONT_OPT(x)
  x = pmadd(y, pset1<Packet>(1.62865035235881805419921875e-07), x); // = 0x342ee000
  x = pmadd(y, pset1<Packet>(5.5644315544167710640977020375430583953857421875e-11), x); // = 0x2e74b9ee

  // For the record, the following set of coefficients maintain 2ULP up
  // to a slightly larger range:
  // const float huge_th = ComputeSine ? 51981.f : 39086.125f;
  // but it slightly fails to maintain 1ULP for two values of sin below pi.
  // x = pmadd(y, pset1<Packet>(-3.140625/2.), x);
  // x = pmadd(y, pset1<Packet>(-0.00048351287841796875), x);
  // x = pmadd(y, pset1<Packet>(-3.13855707645416259765625e-07), x);
  // x = pmadd(y, pset1<Packet>(-6.0771006282767103812147979624569416046142578125e-11), x);

  // For the record, with only 3 iterations it is possible to maintain
  // 1 ULP up to 3PI (maybe more) and 2ULP up to 255.
  // The coefficients are: 0xbfc90f80, 0xb7354480, 0x2e74b9ee
  #endif

  if(predux_any(pcmp_le(pset1<Packet>(huge_th),pabs(_x))))
  {
    const int PacketSize = unpacket_traits<Packet>::size;
    EIGEN_ALIGN_TO_BOUNDARY(sizeof(Packet)) float vals[PacketSize];
    EIGEN_ALIGN_TO_BOUNDARY(sizeof(Packet)) float x_cpy[PacketSize];
    EIGEN_ALIGN_TO_BOUNDARY(sizeof(Packet)) int y_int2[PacketSize];
    pstoreu(vals, pabs(_x));
    pstoreu(x_cpy, x);
    pstoreu(y_int2, y_int);
    for(int k=0; k<PacketSize;++k)
    {
      float val = vals[k];
      if(val>=huge_th && (numext::isfinite)(val))
        x_cpy[k] = trig_reduce_huge(val,&y_int2[k]);
    }
    x = ploadu<Packet>(x_cpy);
    y_int = ploadu<PacketI>(y_int2);
  }

  // Compute the sign to apply to the polynomial.
  // sin: sign = second_bit(y_int) xor signbit(_x)
  // cos: sign = second_bit(y_int+1)
  Packet sign_bit = ComputeSine ? pxor(_x, preinterpret<Packet>(plogical_shift_left<30>(y_int)))
                                : preinterpret<Packet>(plogical_shift_left<30>(padd(y_int,csti_1)));
  sign_bit = pand(sign_bit, cst_sign_mask); // clear all but left most bit

  // Get the polynomial selection mask from the second bit of y_int
  // We'll calculate both (sin and cos) polynomials and then select from the two.
  Packet poly_mask = preinterpret<Packet>(pcmp_eq(pand(y_int, csti_1), pzero(y_int)));

  Packet x2 = pmul(x,x);

  // Evaluate the cos(x) polynomial. (-Pi/4 <= x <= Pi/4)
  Packet y1 =        pset1<Packet>(2.4372266125283204019069671630859375e-05f);
  y1 = pmadd(y1, x2, pset1<Packet>(-0.00138865201734006404876708984375f     ));
  y1 = pmadd(y1, x2, pset1<Packet>(0.041666619479656219482421875f           ));
  y1 = pmadd(y1, x2, pset1<Packet>(-0.5f));
  y1 = pmadd(y1, x2, pset1<Packet>(1.f));

  // Evaluate the sin(x) polynomial. (Pi/4 <= x <= Pi/4)
  // octave/matlab code to compute those coefficients:
  //    x = (0:0.0001:pi/4)';
  //    A = [x.^3 x.^5 x.^7];
  //    w = ((1.-(x/(pi/4)).^2).^5)*2000+1;         # weights trading relative accuracy
  //    c = (A'*diag(w)*A)\(A'*diag(w)*(sin(x)-x)); # weighted LS, linear coeff forced to 1
  //    printf('%.64f\n %.64f\n%.64f\n', c(3), c(2), c(1))
  //
  Packet y2 =        pset1<Packet>(-0.0001959234114083702898469196984621021329076029360294342041015625f);
  y2 = pmadd(y2, x2, pset1<Packet>( 0.0083326873655616851693794799871284340042620897293090820312500000f));
  y2 = pmadd(y2, x2, pset1<Packet>(-0.1666666203982298255503735617821803316473960876464843750000000000f));
  y2 = pmul(y2, x2);
  y2 = pmadd(y2, x, x);

  // Select the correct result from the two polynomials.
  y = ComputeSine ? pselect(poly_mask,y2,y1)
                  : pselect(poly_mask,y1,y2);

  // Update the sign and filter huge inputs
  return pxor(y, sign_bit);

#undef EIGEN_SINCOS_DONT_OPT
}

template<typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet psin_float(const Packet& x)
{
  return psincos_float<true>(x);
}

template<typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet pcos_float(const Packet& x)
{
  return psincos_float<false>(x);
}


template<typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet psqrt_complex(const Packet& a) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  typedef typename Scalar::value_type RealScalar;
  typedef typename unpacket_traits<Packet>::as_real RealPacket;

  // Computes the principal sqrt of the complex numbers in the input.
  //
  // For example, for packets containing 2 complex numbers stored in interleaved format
  //    a = [a0, a1] = [x0, y0, x1, y1],
  // where x0 = real(a0), y0 = imag(a0) etc., this function returns
  //    b = [b0, b1] = [u0, v0, u1, v1],
  // such that b0^2 = a0, b1^2 = a1.
  //
  // To derive the formula for the complex square roots, let's consider the equation for
  // a single complex square root of the number x + i*y. We want to find real numbers
  // u and v such that
  //    (u + i*v)^2 = x + i*y  <=>
  //    u^2 - v^2 + i*2*u*v = x + i*v.
  // By equating the real and imaginary parts we get:
  //    u^2 - v^2 = x
  //    2*u*v = y.
  //
  // For x >= 0, this has the numerically stable solution
  //    u = sqrt(0.5 * (x + sqrt(x^2 + y^2)))
  //    v = 0.5 * (y / u)
  // and for x < 0,
  //    v = sign(y) * sqrt(0.5 * (-x + sqrt(x^2 + y^2)))
  //    u = 0.5 * (y / v)
  //
  //  To avoid unnecessary over- and underflow, we compute sqrt(x^2 + y^2) as
  //     l = max(|x|, |y|) * sqrt(1 + (min(|x|, |y|) / max(|x|, |y|))^2) ,

  // In the following, without lack of generality, we have annotated the code, assuming
  // that the input is a packet of 2 complex numbers.
  //
  // Step 1. Compute l = [l0, l0, l1, l1], where
  //    l0 = sqrt(x0^2 + y0^2),  l1 = sqrt(x1^2 + y1^2)
  // To avoid over- and underflow, we use the stable formula for each hypotenuse
  //    l0 = (min0 == 0 ? max0 : max0 * sqrt(1 + (min0/max0)**2)),
  // where max0 = max(|x0|, |y0|), min0 = min(|x0|, |y0|), and similarly for l1.

  Packet a_flip = pcplxflip(a);
  RealPacket a_abs = pabs(a.v);           // [|x0|, |y0|, |x1|, |y1|]
  RealPacket a_abs_flip = pabs(a_flip.v); // [|y0|, |x0|, |y1|, |x1|]
  RealPacket a_max = pmax(a_abs, a_abs_flip);
  RealPacket a_min = pmin(a_abs, a_abs_flip);
  RealPacket a_min_zero_mask = pcmp_eq(a_min, pzero(a_min));
  RealPacket a_max_zero_mask = pcmp_eq(a_max, pzero(a_max));
  RealPacket r = pdiv(a_min, a_max);
  const RealPacket cst_one  = pset1<RealPacket>(RealScalar(1));
  RealPacket l = pmul(a_max, psqrt(padd(cst_one, pmul(r, r))));  // [l0, l0, l1, l1]
  // Set l to a_max if a_min is zero.
  l = pselect(a_min_zero_mask, a_max, l);

  // Step 2. Compute [rho0, *, rho1, *], where
  // rho0 = sqrt(0.5 * (l0 + |x0|)), rho1 =  sqrt(0.5 * (l1 + |x1|))
  // We don't care about the imaginary parts computed here. They will be overwritten later.
  const RealPacket cst_half = pset1<RealPacket>(RealScalar(0.5));
  Packet rho;
  rho.v = psqrt(pmul(cst_half, padd(a_abs, l)));

  // Step 3. Compute [rho0, eta0, rho1, eta1], where
  // eta0 = (y0 / l0) / 2, and eta1 = (y1 / l1) / 2.
  // set eta = 0 of input is 0 + i0.
  RealPacket eta = pandnot(pmul(cst_half, pdiv(a.v, pcplxflip(rho).v)), a_max_zero_mask);
  RealPacket real_mask = peven_mask(a.v);
  Packet positive_real_result;
  // Compute result for inputs with positive real part.
  positive_real_result.v = pselect(real_mask, rho.v, eta);

  // Step 4. Compute solution for inputs with negative real part:
  //         [|eta0|, sign(y0)*rho0, |eta1|, sign(y1)*rho1]
  const RealPacket cst_imag_sign_mask = pset1<Packet>(Scalar(RealScalar(0.0), RealScalar(-0.0))).v;
  RealPacket imag_signs = pand(a.v, cst_imag_sign_mask);
  Packet negative_real_result;
  // Notice that rho is positive, so taking it's absolute value is a noop.
  negative_real_result.v = por(pabs(pcplxflip(positive_real_result).v), imag_signs);

  // Step 5. Select solution branch based on the sign of the real parts.
  Packet negative_real_mask;
  negative_real_mask.v = pcmp_lt(pand(real_mask, a.v), pzero(a.v));
  negative_real_mask.v = por(negative_real_mask.v, pcplxflip(negative_real_mask).v);
  Packet result = pselect(negative_real_mask, negative_real_result, positive_real_result);

  // Step 6. Handle special cases for infinities:
  // * If z is (x,+∞), the result is (+∞,+∞) even if x is NaN
  // * If z is (x,-∞), the result is (+∞,-∞) even if x is NaN
  // * If z is (-∞,y), the result is (0*|y|,+∞) for finite or NaN y
  // * If z is (+∞,y), the result is (+∞,0*|y|) for finite or NaN y
  const RealPacket cst_pos_inf = pset1<RealPacket>(NumTraits<RealScalar>::infinity());
  Packet is_inf;
  is_inf.v = pcmp_eq(a_abs, cst_pos_inf);
  Packet is_real_inf;
  is_real_inf.v = pand(is_inf.v, real_mask);
  is_real_inf = por(is_real_inf, pcplxflip(is_real_inf));
  // prepare packet of (+∞,0*|y|) or (0*|y|,+∞), depending on the sign of the infinite real part.
  Packet real_inf_result;
  real_inf_result.v = pmul(a_abs, pset1<Packet>(Scalar(RealScalar(1.0), RealScalar(0.0))).v);
  real_inf_result.v = pselect(negative_real_mask.v, pcplxflip(real_inf_result).v, real_inf_result.v);
  // prepare packet of (+∞,+∞) or (+∞,-∞), depending on the sign of the infinite imaginary part.
  Packet is_imag_inf;
  is_imag_inf.v = pandnot(is_inf.v, real_mask);
  is_imag_inf = por(is_imag_inf, pcplxflip(is_imag_inf));
  Packet imag_inf_result;
  imag_inf_result.v = por(pand(cst_pos_inf, real_mask), pandnot(a.v, real_mask));

  return  pselect(is_imag_inf, imag_inf_result,
                  pselect(is_real_inf, real_inf_result,result));
}


// This function implements the Veltkamp splitting. Given a floating point
// number x it returns the pair {x_hi, x_lo} such that x_hi + x_lo = x holds
// exactly and that half of the significant of x fits in x_hi.
// This code corresponds to Algorithms 3 and 4 in
// https://hal.inria.fr/hal-01774587v2/document
template<typename Packet>
EIGEN_STRONG_INLINE
void veltkamp_splitting(const Packet& x, Packet& x_hi, Packet& x_lo) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  EIGEN_CONSTEXPR int shift = (NumTraits<Scalar>::digits() + 1) / 2;
  EIGEN_CONSTEXPR Scalar shift_scale = Scalar(uint64_t(1) << shift);
  Packet gamma = pmul(pset1<Packet>(shift_scale + 1), x);
#ifdef EIGEN_HAS_SINGLE_INSTRUCTION_MADD
  x_hi = pmadd(pset1<Packet>(-shift_scale), x, gamma);
#else
  Packet rho = psub(x, gamma);
  x_hi = padd(rho, gamma);
#endif
  x_lo = psub(x, x_hi);
}

// This function splits x into the nearest integer n and fractional part r,
// such that x = n + r holds exactly.
template<typename Packet>
EIGEN_STRONG_INLINE
void integer_split(const Packet& x, Packet& n, Packet& r) {
  n = pround(x);
  r = psub(x, n);
}

// This function implements Dekker's algorithm for two products {x * y1, x * y2} with
// a shared factor. Given floating point numbers {x, y1, y2} computes the pairs
// {p1, r1} and {p2, r2} such that x * y1 = p1 + r1 holds exactly and
// p1 = fl(x * y1), and x * y2 = p2 + r2 holds exactly and p2 = fl(x * y2).
template<typename Packet>
EIGEN_STRONG_INLINE
void double_dekker(const Packet& x, const Packet& y1, const Packet& y2,
                   Packet& p1, Packet& r1, Packet& p2, Packet& r2) {
  Packet x_hi, x_lo, y1_hi, y1_lo, y2_hi, y2_lo;
  veltkamp_splitting(x, x_hi, x_lo);
  veltkamp_splitting(y1, y1_hi, y1_lo);
  veltkamp_splitting(y2, y2_hi, y2_lo);

  p1 = pmul(x, y1);
  r1 = pmadd(x_hi, y1_hi, pnegate(p1));
  r1 = pmadd(x_hi, y1_lo, r1);
  r1 = pmadd(x_lo, y1_hi, r1);
  r1 = pmadd(x_lo, y1_lo, r1);

  p2 = pmul(x, y2);
  r2 = pmadd(x_hi, y2_hi, pnegate(p2));
  r2 = pmadd(x_hi, y2_lo, r2);
  r2 = pmadd(x_lo, y2_hi, r2);
  r2 = pmadd(x_lo, y2_lo, r2);
}

// This function implements the non-trivial case of pow(x,y) where x is
// positive and y is (possibly) non-integer.
// Formally, pow(x,y) = 2**(y * log2(x))
template<typename Packet>
EIGEN_STRONG_INLINE
Packet generic_pow_impl(const Packet& x, const Packet& y) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  // Split x into exponent e_x and mantissa m_x.
  Packet e_x;
  Packet m_x = pfrexp(x, e_x);

  // Adjust m_x to lie in [0.75:1.5) to minimize absolute error in log2(m_x).
  Packet m_x_scale_mask = pcmp_lt(m_x, pset1<Packet>(Scalar(0.75)));
  m_x = pselect(m_x_scale_mask, pmul(pset1<Packet>(Scalar(2)), m_x), m_x);
  e_x = pselect(m_x_scale_mask, psub(e_x, pset1<Packet>(Scalar(1))), e_x);

  Packet r_x = plog2(m_x);

  // Compute the two terms {y * e_x, y * r_x} in f = y * log2(x) with doubled
  // precision using Dekker's algorithm.
  Packet f1_hi, f1_lo, f2_hi, f2_lo;
  double_dekker(y, e_x, r_x, f1_hi, f1_lo, f2_hi, f2_lo);

  // Separate f into integer and fractional parts, keeping f1_hi, and f2_hi
  // separate to avoid cancellation.
  Packet n1, r1, n2, r2;
  integer_split(f1_hi, n1, r1);
  integer_split(f2_hi, n2, r2);

  // Add up integer parts and sum the remainders.
  Packet n_z = padd(n1, n2);
  // Notice: I experimented with using compensated (Kahan) summation here,
  // but it does not seem to matter.
  Packet rem = padd(padd(f1_lo, f2_lo), padd(r1, r2));

  // Extract any additional integer part that may have accumulated in rem.
  Packet nrem, r_z;
  integer_split(rem, nrem, r_z);
  n_z = padd(n_z, nrem);

  // We now have an accurate split of f = n_z + r_z and can compute
  // x^y = 2**{n_z + r_z) = exp(ln(2) * r_z) * 2**{n_z}.
  // The first factor we compute by calling pexp(), while multiplication
  // by an integer power of 2 can be done exactly using pldexp().
  // Note: I experimented with using Dekker's algorithms for the
  // multiplication by ln(2) here, but did not see any difference.
  Packet e_r = pexp(pmul(pset1<Packet>(Scalar(EIGEN_LN2)), r_z));
  return pldexp(e_r, n_z);
}

// Generic implementation of pow(x,y).
template<typename Packet>
EIGEN_DEFINE_FUNCTION_ALLOWING_MULTIPLE_DEFINITIONS
EIGEN_UNUSED
Packet generic_pow(const Packet& x, const Packet& y) {
  typedef typename unpacket_traits<Packet>::type Scalar;
  const Packet cst_pos_inf = pset1<Packet>(NumTraits<Scalar>::infinity());
  const Packet cst_zero = pset1<Packet>(Scalar(0));
  const Packet cst_one = pset1<Packet>(Scalar(1));
  const Packet cst_nan = pset1<Packet>(NumTraits<Scalar>::quiet_NaN());

  Packet abs_x = pabs(x);
  // Predicates for sign and magnitude of x.
  Packet x_is_zero = pcmp_eq(x, cst_zero);
  Packet x_is_neg = pcmp_lt(x, cst_zero);
  Packet abs_x_is_inf = pcmp_eq(abs_x, cst_pos_inf);
  Packet abs_x_is_one =  pcmp_eq(abs_x, cst_one);
  Packet abs_x_is_gt_one = pcmp_lt(cst_one, abs_x);
  Packet abs_x_is_lt_one = pcmp_lt(abs_x, cst_one);
  Packet x_is_one =  pandnot(abs_x_is_one, x_is_neg);
  Packet x_is_neg_one =  pand(abs_x_is_one, x_is_neg);
  Packet x_is_nan = pandnot(ptrue(x), pcmp_eq(x, x));

  // Predicates for sign and magnitude of y.
  Packet y_is_zero = pcmp_eq(y, cst_zero);
  Packet y_is_neg = pcmp_lt(y, cst_zero);
  Packet y_is_pos = pandnot(ptrue(y), por(y_is_zero, y_is_neg));
  Packet y_is_nan = pandnot(ptrue(y), pcmp_eq(y, y));
  Packet abs_y_is_inf = pcmp_eq(pabs(y), cst_pos_inf);

  // Predicates for whether y is integer and/or even.
  Packet y_is_int = pcmp_eq(pfloor(y), y);
  Packet y_div_2 = pldexp(y, pset1<Packet>(Scalar(-1)));
  Packet y_is_even = pcmp_eq(pround(y_div_2), y_div_2);

  // Predicates encoding special cases for the value of pow(x,y)
  Packet invalid_negative_x = pandnot(pandnot(pandnot(x_is_neg, abs_x_is_inf), y_is_int), abs_y_is_inf);
  Packet pow_is_nan = por(invalid_negative_x, por(x_is_nan, y_is_nan));
  Packet pow_is_one = por(por(y_is_zero, x_is_one), pand(x_is_neg_one, abs_y_is_inf));
  Packet pow_is_zero = por(por(por(pand(x_is_zero, y_is_pos), pand(abs_x_is_inf, y_is_neg)),
                               pand(pand(abs_x_is_lt_one, abs_y_is_inf), y_is_pos)),
                           pand(pand(abs_x_is_gt_one, abs_y_is_inf), y_is_neg));
  Packet pow_is_inf = por(por(por(pand(x_is_zero, y_is_neg), pand(abs_x_is_inf, y_is_pos)),
                              pand(pand(abs_x_is_lt_one, abs_y_is_inf), y_is_neg)),
                          pand(pand(abs_x_is_gt_one, abs_y_is_inf), y_is_pos));

  // General computation of pow(x,y) for positive x or negative x and integer y.
  Packet negate_pow_abs = pandnot(x_is_neg, y_is_even);
  Packet pow_abs = generic_pow_impl(abs_x, y);

  return pselect(pow_is_one, cst_one,
                 pselect(pow_is_nan, cst_nan,
                         pselect(pow_is_inf, cst_pos_inf,
                                 pselect(pow_is_zero, cst_zero,
                                         pselect(negate_pow_abs, pnegate(pow_abs), pow_abs)))));
}


/* polevl (modified for Eigen)
 *
 *      Evaluate polynomial
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * Scalar x, y, coef[N+1];
 *
 * y = polevl<decltype(x), N>( x, coef);
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates polynomial of degree N:
 *
 *                     2          N
 * y  =  C  + C x + C x  +...+ C x
 *        0    1     2          N
 *
 * Coefficients are stored in reverse order:
 *
 * coef[0] = C  , ..., coef[N] = C  .
 *            N                   0
 *
 *  The function p1evl() assumes that coef[N] = 1.0 and is
 * omitted from the array.  Its calling arguments are
 * otherwise the same as polevl().
 *
 *
 * The Eigen implementation is templatized.  For best speed, store
 * coef as a const array (constexpr), e.g.
 *
 * const double coef[] = {1.0, 2.0, 3.0, ...};
 *
 */
template <typename Packet, int N>
struct ppolevl {
  static EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Packet run(const Packet& x, const typename unpacket_traits<Packet>::type coeff[]) {
    EIGEN_STATIC_ASSERT((N > 0), YOU_MADE_A_PROGRAMMING_MISTAKE);
    return pmadd(ppolevl<Packet, N-1>::run(x, coeff), x, pset1<Packet>(coeff[N]));
  }
};

template <typename Packet>
struct ppolevl<Packet, 0> {
  static EIGEN_DEVICE_FUNC EIGEN_STRONG_INLINE Packet run(const Packet& x, const typename unpacket_traits<Packet>::type coeff[]) {
    EIGEN_UNUSED_VARIABLE(x);
    return pset1<Packet>(coeff[0]);
  }
};

/* chbevl (modified for Eigen)
 *
 *     Evaluate Chebyshev series
 *
 *
 *
 * SYNOPSIS:
 *
 * int N;
 * Scalar x, y, coef[N], chebevl();
 *
 * y = chbevl( x, coef, N );
 *
 *
 *
 * DESCRIPTION:
 *
 * Evaluates the series
 *
 *        N-1
 *         - '
 *  y  =   >   coef[i] T (x/2)
 *         -            i
 *        i=0
 *
 * of Chebyshev polynomials Ti at argument x/2.
 *
 * Coefficients are stored in reverse order, i.e. the zero
 * order term is last in the array.  Note N is the number of
 * coefficients, not the order.
 *
 * If coefficients are for the interval a to b, x must
 * have been transformed to x -> 2(2x - b - a)/(b-a) before
 * entering the routine.  This maps x from (a, b) to (-1, 1),
 * over which the Chebyshev polynomials are defined.
 *
 * If the coefficients are for the inverted interval, in
 * which (a, b) is mapped to (1/b, 1/a), the transformation
 * required is x -> 2(2ab/x - b - a)/(b-a).  If b is infinity,
 * this becomes x -> 4a/x - 1.
 *
 *
 *
 * SPEED:
 *
 * Taking advantage of the recurrence properties of the
 * Chebyshev polynomials, the routine requires one more
 * addition per loop than evaluating a nested polynomial of
 * the same degree.
 *
 */

template <typename Packet, int N>
struct pchebevl {
  EIGEN_DEVICE_FUNC
  static EIGEN_STRONG_INLINE Packet run(Packet x, const typename unpacket_traits<Packet>::type coef[]) {
    typedef typename unpacket_traits<Packet>::type Scalar;
    Packet b0 = pset1<Packet>(coef[0]);
    Packet b1 = pset1<Packet>(static_cast<Scalar>(0.f));
    Packet b2;

    for (int i = 1; i < N; i++) {
      b2 = b1;
      b1 = b0;
      b0 = psub(pmadd(x, b1, pset1<Packet>(coef[i])), b2);
    }

    return pmul(pset1<Packet>(static_cast<Scalar>(0.5f)), psub(b0, b2));
  }
};

} // end namespace internal
} // end namespace Eigen

#endif // EIGEN_ARCH_GENERIC_PACKET_MATH_FUNCTIONS_H
