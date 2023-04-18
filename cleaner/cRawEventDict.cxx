// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cRawEventDict

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
#include "../src/cRawEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_cRawEvent(void *p = 0);
   static void *newArray_cRawEvent(Long_t size, void *p);
   static void delete_cRawEvent(void *p);
   static void deleteArray_cRawEvent(void *p);
   static void destruct_cRawEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cRawEvent*)
   {
      ::cRawEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cRawEvent >(0);
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
      return GenerateInitInstanceLocal((::cRawEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cRawEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cRawEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *cRawEvent::Class_Name()
{
   return "cRawEvent";
}

//______________________________________________________________________________
const char *cRawEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int cRawEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cRawEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cRawEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cRawEvent*)0x0)->GetClass(); }
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
   static void *new_vectorlEcHitgR(void *p = 0);
   static void *newArray_vectorlEcHitgR(Long_t size, void *p);
   static void delete_vectorlEcHitgR(void *p);
   static void deleteArray_vectorlEcHitgR(void *p);
   static void destruct_vectorlEcHitgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<cHit>*)
   {
      vector<cHit> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<cHit>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<cHit>", -2, "vector", 339,
                  typeid(vector<cHit>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcHitgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<cHit>) );
      instance.SetNew(&new_vectorlEcHitgR);
      instance.SetNewArray(&newArray_vectorlEcHitgR);
      instance.SetDelete(&delete_vectorlEcHitgR);
      instance.SetDeleteArray(&deleteArray_vectorlEcHitgR);
      instance.SetDestructor(&destruct_vectorlEcHitgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<cHit> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<cHit>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcHitgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<cHit>*)0x0)->GetClass();
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
0
    };
    static const char* includePaths[] = {
"/home/software/root/include",
"/home/camaiani/ATS_ne20/cleaner/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cRawEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../src/cRawEvent.h")))  cRawEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cRawEventDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../src/cRawEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"cRawEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cRawEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cRawEventDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
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
