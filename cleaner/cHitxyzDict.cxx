// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cHitxyzDict

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
#include "../src/cHitxyz.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_cHitxyz(void *p = 0);
   static void *newArray_cHitxyz(Long_t size, void *p);
   static void delete_cHitxyz(void *p);
   static void deleteArray_cHitxyz(void *p);
   static void destruct_cHitxyz(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cHitxyz*)
   {
      ::cHitxyz *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cHitxyz >(0);
      static ::ROOT::TGenericClassInfo 
         instance("cHitxyz", ::cHitxyz::Class_Version(), "../src/cHitxyz.h", 11,
                  typeid(::cHitxyz), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::cHitxyz::Dictionary, isa_proxy, 4,
                  sizeof(::cHitxyz) );
      instance.SetNew(&new_cHitxyz);
      instance.SetNewArray(&newArray_cHitxyz);
      instance.SetDelete(&delete_cHitxyz);
      instance.SetDeleteArray(&deleteArray_cHitxyz);
      instance.SetDestructor(&destruct_cHitxyz);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cHitxyz*)
   {
      return GenerateInitInstanceLocal((::cHitxyz*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cHitxyz*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cHitxyz::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *cHitxyz::Class_Name()
{
   return "cHitxyz";
}

//______________________________________________________________________________
const char *cHitxyz::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cHitxyz*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int cHitxyz::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cHitxyz*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cHitxyz::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cHitxyz*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cHitxyz::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cHitxyz*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void cHitxyz::Streamer(TBuffer &R__b)
{
   // Stream an object of class cHitxyz.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(cHitxyz::Class(),this);
   } else {
      R__b.WriteClassBuffer(cHitxyz::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cHitxyz(void *p) {
      return  p ? new(p) ::cHitxyz : new ::cHitxyz;
   }
   static void *newArray_cHitxyz(Long_t nElements, void *p) {
      return p ? new(p) ::cHitxyz[nElements] : new ::cHitxyz[nElements];
   }
   // Wrapper around operator delete
   static void delete_cHitxyz(void *p) {
      delete ((::cHitxyz*)p);
   }
   static void deleteArray_cHitxyz(void *p) {
      delete [] ((::cHitxyz*)p);
   }
   static void destruct_cHitxyz(void *p) {
      typedef ::cHitxyz current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cHitxyz

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
  void TriggerDictionaryInitialization_cHitxyzDict_Impl() {
    static const char* headers[] = {
"../src/cHitxyz.h",
0
    };
    static const char* includePaths[] = {
"/home/software/root/include",
"/home/camaiani/ATS_ne20/cleaner/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cHitxyzDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../src/cHitxyz.h")))  cHitxyz;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cHitxyzDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../src/cHitxyz.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"cHitxyz", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cHitxyzDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cHitxyzDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_cHitxyzDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_cHitxyzDict() {
  TriggerDictionaryInitialization_cHitxyzDict_Impl();
}
