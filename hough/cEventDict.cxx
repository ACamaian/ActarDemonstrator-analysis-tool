// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cEventDict
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
#include "../src/cEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_cEvent(void *p = nullptr);
   static void *newArray_cEvent(Long_t size, void *p);
   static void delete_cEvent(void *p);
   static void deleteArray_cEvent(void *p);
   static void destruct_cEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cEvent*)
   {
      ::cEvent *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cEvent >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("cEvent", ::cEvent::Class_Version(), "../src/cEvent.h", 14,
                  typeid(::cEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::cEvent::Dictionary, isa_proxy, 4,
                  sizeof(::cEvent) );
      instance.SetNew(&new_cEvent);
      instance.SetNewArray(&newArray_cEvent);
      instance.SetDelete(&delete_cEvent);
      instance.SetDeleteArray(&deleteArray_cEvent);
      instance.SetDestructor(&destruct_cEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cEvent*)
   {
      return GenerateInitInstanceLocal((::cEvent*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cEvent*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cEvent::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *cEvent::Class_Name()
{
   return "cEvent";
}

//______________________________________________________________________________
const char *cEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cEvent*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int cEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cEvent*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cEvent*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cEvent*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void cEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class cEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(cEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(cEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cEvent(void *p) {
      return  p ? new(p) ::cEvent : new ::cEvent;
   }
   static void *newArray_cEvent(Long_t nElements, void *p) {
      return p ? new(p) ::cEvent[nElements] : new ::cEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_cEvent(void *p) {
      delete ((::cEvent*)p);
   }
   static void deleteArray_cEvent(void *p) {
      delete [] ((::cEvent*)p);
   }
   static void destruct_cEvent(void *p) {
      typedef ::cEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cEvent

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = nullptr);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 389,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)nullptr)->GetClass();
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

namespace ROOT {
   static TClass *vectorlEcHitxyzgR_Dictionary();
   static void vectorlEcHitxyzgR_TClassManip(TClass*);
   static void *new_vectorlEcHitxyzgR(void *p = nullptr);
   static void *newArray_vectorlEcHitxyzgR(Long_t size, void *p);
   static void delete_vectorlEcHitxyzgR(void *p);
   static void deleteArray_vectorlEcHitxyzgR(void *p);
   static void destruct_vectorlEcHitxyzgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<cHitxyz>*)
   {
      vector<cHitxyz> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<cHitxyz>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<cHitxyz>", -2, "vector", 389,
                  typeid(vector<cHitxyz>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEcHitxyzgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<cHitxyz>) );
      instance.SetNew(&new_vectorlEcHitxyzgR);
      instance.SetNewArray(&newArray_vectorlEcHitxyzgR);
      instance.SetDelete(&delete_vectorlEcHitxyzgR);
      instance.SetDeleteArray(&deleteArray_vectorlEcHitxyzgR);
      instance.SetDestructor(&destruct_vectorlEcHitxyzgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<cHitxyz> >()));

      ::ROOT::AddClassAlternate("vector<cHitxyz>","std::vector<cHitxyz, std::allocator<cHitxyz> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<cHitxyz>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEcHitxyzgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<cHitxyz>*)nullptr)->GetClass();
      vectorlEcHitxyzgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEcHitxyzgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEcHitxyzgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cHitxyz> : new vector<cHitxyz>;
   }
   static void *newArray_vectorlEcHitxyzgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<cHitxyz>[nElements] : new vector<cHitxyz>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEcHitxyzgR(void *p) {
      delete ((vector<cHitxyz>*)p);
   }
   static void deleteArray_vectorlEcHitxyzgR(void *p) {
      delete [] ((vector<cHitxyz>*)p);
   }
   static void destruct_vectorlEcHitxyzgR(void *p) {
      typedef vector<cHitxyz> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<cHitxyz>

namespace ROOT {
   static TClass *maplEintcOvectorlEdoublegRsPgR_Dictionary();
   static void maplEintcOvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_maplEintcOvectorlEdoublegRsPgR(void *p = nullptr);
   static void *newArray_maplEintcOvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_maplEintcOvectorlEdoublegRsPgR(void *p);
   static void deleteArray_maplEintcOvectorlEdoublegRsPgR(void *p);
   static void destruct_maplEintcOvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,vector<double> >*)
   {
      map<int,vector<double> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,vector<double> >", -2, "map", 100,
                  typeid(map<int,vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOvectorlEdoublegRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,vector<double> >) );
      instance.SetNew(&new_maplEintcOvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_maplEintcOvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_maplEintcOvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_maplEintcOvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,vector<double> > >()));

      ::ROOT::AddClassAlternate("map<int,vector<double> >","std::map<int, std::vector<double, std::allocator<double> >, std::less<int>, std::allocator<std::pair<int const, std::vector<double, std::allocator<double> > > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,vector<double> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,vector<double> >*)nullptr)->GetClass();
      maplEintcOvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<double> > : new map<int,vector<double> >;
   }
   static void *newArray_maplEintcOvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,vector<double> >[nElements] : new map<int,vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOvectorlEdoublegRsPgR(void *p) {
      delete ((map<int,vector<double> >*)p);
   }
   static void deleteArray_maplEintcOvectorlEdoublegRsPgR(void *p) {
      delete [] ((map<int,vector<double> >*)p);
   }
   static void destruct_maplEintcOvectorlEdoublegRsPgR(void *p) {
      typedef map<int,vector<double> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,vector<double> >

namespace {
  void TriggerDictionaryInitialization_cEventDict_Impl() {
    static const char* headers[] = {
"../src/cEvent.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/software/root/include/",
"/home/camaiani/ATS_ne20/hough/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cEventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$../src/cEvent.h")))  cEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cEventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "../src/cEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"cEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cEventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cEventDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_cEventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_cEventDict() {
  TriggerDictionaryInitialization_cEventDict_Impl();
}
