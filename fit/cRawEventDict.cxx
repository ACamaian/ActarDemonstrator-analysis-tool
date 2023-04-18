// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cRawEventDict
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
#include "../src/cRawEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_cRawEvent(void *p = nullptr);
   static void *newArray_cRawEvent(Long_t size, void *p);
   static void delete_cRawEvent(void *p);
   static void deleteArray_cRawEvent(void *p);
   static void destruct_cRawEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cRawEvent*)
   {
      ::cRawEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cRawEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("cRawEvent", ::cRawEvent::Class_Version(), "../src/cRawEvent.h", 13,
                  typeid(::cRawEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::cRawEvent::Dictionary, isa_proxy, 4,
                  sizeof(::cRawEvent) );
      instance.SetNew(&new_cRawEvent);
      instance.SetNewArray(&newArray_cRawEvent);
      instance.SetDelete(&delete_cRawEvent);
      instance.SetDeleteArray(&deleteArray_cRawEvent);
      instance.SetDestructor(&destruct_cRawEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cRawEvent*)
   {
      return GenerateInitInstanceLocal((::cRawEvent*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cRawEvent*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cRawEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *cRawEvent::Class_Name()
{
   return "cRawEvent";
}

//______________________________________________________________________________
const char *cRawEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int cRawEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cRawEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cRawEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void cRawEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class cRawEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(cRawEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(cRawEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cRawEvent(void *p) {
      return  p ? new(p) ::cRawEvent : new ::cRawEvent;
   }
   static void *newArray_cRawEvent(Long_t nElements, void *p) {
      return p ? new(p) ::cRawEvent[nElements] : new ::cRawEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_cRawEvent(void *p) {
      delete ((::cRawEvent*)p);
   }
   static void deleteArray_cRawEvent(void *p) {
      delete [] ((::cRawEvent*)p);
   }
   static void destruct_cRawEvent(void *p) {
      typedef ::cRawEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cRawEvent

namespace ROOT {
   static TClass *vectorlEcHitgR_Dictionary();
   static void vectorlEcHitgR_TClassManip(TClass*);
   static void *new_vectorlEcHitgR(void *p = nullptr);
   static void *newArray_vectorlEcHitgR(Long_t size, void *p);
   static void delete_vectorlEcHitgR(void *p);
   static void deleteArray_vectorlEcHitgR(void *p);
   static void destruct_vectorlEcHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<cHit>*)
   {
      vector<cHit> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<cHit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<cHit>", -2, "vector", 389,
                  typeid(vector<cHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcHitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<cHit>) );
      instance.SetNew(&new_vectorlEcHitgR);
      instance.SetNewArray(&newArray_vectorlEcHitgR);
      instance.SetDelete(&delete_vectorlEcHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlEcHitgR);
      instance.SetDestructor(&destruct_vectorlEcHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<cHit> >()));

      ::ROOT::AddClassAlternate("vector<cHit>","std::vector<cHit, std::allocator<cHit> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<cHit>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<cHit>*)nullptr)->GetClass();
      vectorlEcHitgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEcHitgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEcHitgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cHit> : new vector<cHit>;
   }
   static void *newArray_vectorlEcHitgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cHit>[nElements] : new vector<cHit>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEcHitgR(void *p) {
      delete ((vector<cHit>*)p);
   }
   static void deleteArray_vectorlEcHitgR(void *p) {
      delete [] ((vector<cHit>*)p);
   }
   static void destruct_vectorlEcHitgR(void *p) {
      typedef vector<cHit> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<cHit>

namespace {
  void TriggerDictionaryInitialization_cRawEventDict_Impl() {
    static const char* headers[] = {
"../src/cRawEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/software/root/include/",
"/home/camaiani/ATS_ne20/fit/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cRawEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$../src/cRawEvent.h")))  cRawEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cRawEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "../src/cRawEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"cRawEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cRawEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cRawEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_cRawEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_cRawEventDict() {
  TriggerDictionaryInitialization_cRawEventDict_Impl();
}
