// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME pSignalDict
#define R__NO_DEPRECATION

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

// Header files passed as explicit arguments
#include "../src/pSignal.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_pSignal(void *p = nullptr);
   static void *newArray_pSignal(Long_t size, void *p);
   static void delete_pSignal(void *p);
   static void deleteArray_pSignal(void *p);
   static void destruct_pSignal(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::pSignal*)
   {
      ::pSignal *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::pSignal >(nullptr);
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
      return GenerateInitInstanceLocal((::pSignal*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::pSignal*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr pSignal::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *pSignal::Class_Name()
{
   return "pSignal";
}

//______________________________________________________________________________
const char *pSignal::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int pSignal::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *pSignal::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *pSignal::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::pSignal*)nullptr)->GetClass(); }
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
nullptr
    };
    static const char* includePaths[] = {
"/home/software/root/include/",
"/home/camaiani/ATS_ne20/fit/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "pSignalDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$../src/pSignal.h")))  pSignal;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "pSignalDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "../src/pSignal.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"pSignal", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("pSignalDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_pSignalDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
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
