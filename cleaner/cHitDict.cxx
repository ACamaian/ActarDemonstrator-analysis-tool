// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cHitDict

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
#include "../src/cHit.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_cHit(void *p = 0);
   static void *newArray_cHit(Long_t size, void *p);
   static void delete_cHit(void *p);
   static void deleteArray_cHit(void *p);
   static void destruct_cHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cHit*)
   {
      ::cHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("cHit", ::cHit::Class_Version(), "../src/cHit.h", 11,
                  typeid(::cHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::cHit::Dictionary, isa_proxy, 4,
                  sizeof(::cHit) );
      instance.SetNew(&new_cHit);
      instance.SetNewArray(&newArray_cHit);
      instance.SetDelete(&delete_cHit);
      instance.SetDeleteArray(&deleteArray_cHit);
      instance.SetDestructor(&destruct_cHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cHit*)
   {
      return GenerateInitInstanceLocal((::cHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cHit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *cHit::Class_Name()
{
   return "cHit";
}

//______________________________________________________________________________
const char *cHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int cHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void cHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class cHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(cHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(cHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cHit(void *p) {
      return  p ? new(p) ::cHit : new ::cHit;
   }
   static void *newArray_cHit(Long_t nElements, void *p) {
      return p ? new(p) ::cHit[nElements] : new ::cHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_cHit(void *p) {
      delete ((::cHit*)p);
   }
   static void deleteArray_cHit(void *p) {
      delete [] ((::cHit*)p);
   }
   static void destruct_cHit(void *p) {
      typedef ::cHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cHit

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 339,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_cHitDict_Impl() {
    static const char* headers[] = {
"../src/cHit.h",
0
    };
    static const char* includePaths[] = {
"/home/software/root/include",
"/home/camaiani/ATS_ne20/cleaner/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cHitDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../src/cHit.h")))  cHit;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cHitDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../src/cHit.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"cHit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cHitDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cHitDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_cHitDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_cHitDict() {
  TriggerDictionaryInitialization_cHitDict_Impl();
}
