// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME pSignalDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "../src/pSignal.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_pSignal(void *p = 0);
   static void *newArray_pSignal(Long_t size, void *p);
   static void delete_pSignal(void *p);
   static void deleteArray_pSignal(void *p);
   static void destruct_pSignal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::pSignal*)
   {
      ::pSignal *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::pSignal >(0);
      static ::ROOT::TGenericClassInfo 
         instance("pSignal", ::pSignal::Class_Version(), "../src/pSignal.h", 43,
                  typeid(::pSignal), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::pSignal::Dictionary, isa_proxy, 4,
                  sizeof(::pSignal) );
      instance.SetNew(&new_pSignal);
      instance.SetNewArray(&newArray_pSignal);
      instance.SetDelete(&delete_pSignal);
      instance.SetDeleteArray(&deleteArray_pSignal);
      instance.SetDestructor(&destruct_pSignal);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::pSignal*)
   {
      return GenerateInitInstanceLocal((::pSignal*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::pSignal*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr pSignal::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *pSignal::Class_Name()
{
   return "pSignal";
}

//______________________________________________________________________________
const char *pSignal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int pSignal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *pSignal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *pSignal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void pSignal::Streamer(TBuffer &R__b)
{
   // Stream an object of class pSignal.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(pSignal::Class(),this);
   } else {
      R__b.WriteClassBuffer(pSignal::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_pSignal(void *p) {
      return  p ? new(p) ::pSignal : new ::pSignal;
   }
   static void *newArray_pSignal(Long_t nElements, void *p) {
      return p ? new(p) ::pSignal[nElements] : new ::pSignal[nElements];
   }
   // Wrapper around operator delete
   static void delete_pSignal(void *p) {
      delete ((::pSignal*)p);
   }
   static void deleteArray_pSignal(void *p) {
      delete [] ((::pSignal*)p);
   }
   static void destruct_pSignal(void *p) {
      typedef ::pSignal current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::pSignal

namespace {
  void TriggerDictionaryInitialization_pSignalDict_Impl() {
    static const char* headers[] = {
"../src/pSignal.h",
0
    };
    static const char* includePaths[] = {
"/home/software/root/include",
"/home/camaiani/ATS_ne20/cleaner/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "pSignalDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../src/pSignal.h")))  pSignal;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "pSignalDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../src/pSignal.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"pSignal", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("pSignalDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_pSignalDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_pSignalDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_pSignalDict() {
  TriggerDictionaryInitialization_pSignalDict_Impl();
}
