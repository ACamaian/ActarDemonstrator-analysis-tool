// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME cLookupTableDict
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
#include "../src/cLookupTable.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_cLookupTable(void *p = nullptr);
   static void *newArray_cLookupTable(Long_t size, void *p);
   static void delete_cLookupTable(void *p);
   static void deleteArray_cLookupTable(void *p);
   static void destruct_cLookupTable(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::cLookupTable*)
   {
      ::cLookupTable *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::cLookupTable >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("cLookupTable", ::cLookupTable::Class_Version(), "../src/cLookupTable.h", 13,
                  typeid(::cLookupTable), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::cLookupTable::Dictionary, isa_proxy, 4,
                  sizeof(::cLookupTable) );
      instance.SetNew(&new_cLookupTable);
      instance.SetNewArray(&newArray_cLookupTable);
      instance.SetDelete(&delete_cLookupTable);
      instance.SetDeleteArray(&deleteArray_cLookupTable);
      instance.SetDestructor(&destruct_cLookupTable);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::cLookupTable*)
   {
      return GenerateInitInstanceLocal((::cLookupTable*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::cLookupTable*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr cLookupTable::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *cLookupTable::Class_Name()
{
   return "cLookupTable";
}

//______________________________________________________________________________
const char *cLookupTable::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cLookupTable*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int cLookupTable::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::cLookupTable*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *cLookupTable::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cLookupTable*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *cLookupTable::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::cLookupTable*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void cLookupTable::Streamer(TBuffer &R__b)
{
   // Stream an object of class cLookupTable.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(cLookupTable::Class(),this);
   } else {
      R__b.WriteClassBuffer(cLookupTable::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_cLookupTable(void *p) {
      return  p ? new(p) ::cLookupTable : new ::cLookupTable;
   }
   static void *newArray_cLookupTable(Long_t nElements, void *p) {
      return p ? new(p) ::cLookupTable[nElements] : new ::cLookupTable[nElements];
   }
   // Wrapper around operator delete
   static void delete_cLookupTable(void *p) {
      delete ((::cLookupTable*)p);
   }
   static void deleteArray_cLookupTable(void *p) {
      delete [] ((::cLookupTable*)p);
   }
   static void destruct_cLookupTable(void *p) {
      typedef ::cLookupTable current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::cLookupTable

namespace ROOT {
   static TClass *maplEintcOcLookupTablecLcLchanDatagR_Dictionary();
   static void maplEintcOcLookupTablecLcLchanDatagR_TClassManip(TClass*);
   static void *new_maplEintcOcLookupTablecLcLchanDatagR(void *p = nullptr);
   static void *newArray_maplEintcOcLookupTablecLcLchanDatagR(Long_t size, void *p);
   static void delete_maplEintcOcLookupTablecLcLchanDatagR(void *p);
   static void deleteArray_maplEintcOcLookupTablecLcLchanDatagR(void *p);
   static void destruct_maplEintcOcLookupTablecLcLchanDatagR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,cLookupTable::chanData>*)
   {
      map<int,cLookupTable::chanData> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,cLookupTable::chanData>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,cLookupTable::chanData>", -2, "map", 100,
                  typeid(map<int,cLookupTable::chanData>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOcLookupTablecLcLchanDatagR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,cLookupTable::chanData>) );
      instance.SetNew(&new_maplEintcOcLookupTablecLcLchanDatagR);
      instance.SetNewArray(&newArray_maplEintcOcLookupTablecLcLchanDatagR);
      instance.SetDelete(&delete_maplEintcOcLookupTablecLcLchanDatagR);
      instance.SetDeleteArray(&deleteArray_maplEintcOcLookupTablecLcLchanDatagR);
      instance.SetDestructor(&destruct_maplEintcOcLookupTablecLcLchanDatagR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,cLookupTable::chanData> >()));

      ::ROOT::AddClassAlternate("map<int,cLookupTable::chanData>","std::map<int, cLookupTable::chanData, std::less<int>, std::allocator<std::pair<int const, cLookupTable::chanData> > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,cLookupTable::chanData>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOcLookupTablecLcLchanDatagR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,cLookupTable::chanData>*)nullptr)->GetClass();
      maplEintcOcLookupTablecLcLchanDatagR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOcLookupTablecLcLchanDatagR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOcLookupTablecLcLchanDatagR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,cLookupTable::chanData> : new map<int,cLookupTable::chanData>;
   }
   static void *newArray_maplEintcOcLookupTablecLcLchanDatagR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,cLookupTable::chanData>[nElements] : new map<int,cLookupTable::chanData>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOcLookupTablecLcLchanDatagR(void *p) {
      delete ((map<int,cLookupTable::chanData>*)p);
   }
   static void deleteArray_maplEintcOcLookupTablecLcLchanDatagR(void *p) {
      delete [] ((map<int,cLookupTable::chanData>*)p);
   }
   static void destruct_maplEintcOcLookupTablecLcLchanDatagR(void *p) {
      typedef map<int,cLookupTable::chanData> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,cLookupTable::chanData>

namespace ROOT {
   static TClass *listlEstringgR_Dictionary();
   static void listlEstringgR_TClassManip(TClass*);
   static void *new_listlEstringgR(void *p = nullptr);
   static void *newArray_listlEstringgR(Long_t size, void *p);
   static void delete_listlEstringgR(void *p);
   static void deleteArray_listlEstringgR(void *p);
   static void destruct_listlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const list<string>*)
   {
      list<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(list<string>));
      static ::ROOT::TGenericClassInfo 
         instance("list<string>", -2, "list", 556,
                  typeid(list<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &listlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(list<string>) );
      instance.SetNew(&new_listlEstringgR);
      instance.SetNewArray(&newArray_listlEstringgR);
      instance.SetDelete(&delete_listlEstringgR);
      instance.SetDeleteArray(&deleteArray_listlEstringgR);
      instance.SetDestructor(&destruct_listlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< list<string> >()));

      ::ROOT::AddClassAlternate("list<string>","std::__cxx11::list<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const list<string>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *listlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const list<string>*)nullptr)->GetClass();
      listlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void listlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_listlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<string> : new list<string>;
   }
   static void *newArray_listlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) list<string>[nElements] : new list<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_listlEstringgR(void *p) {
      delete ((list<string>*)p);
   }
   static void deleteArray_listlEstringgR(void *p) {
      delete [] ((list<string>*)p);
   }
   static void destruct_listlEstringgR(void *p) {
      typedef list<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class list<string>

namespace {
  void TriggerDictionaryInitialization_cLookupTableDict_Impl() {
    static const char* headers[] = {
"../src/cLookupTable.h",
nullptr
    };
    static const char* includePaths[] = {
"/home/software/root/include/",
"/home/camaiani/ATS_ne20/simul/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "cLookupTableDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$../src/cLookupTable.h")))  cLookupTable;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "cLookupTableDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "../src/cLookupTable.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"cLookupTable", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("cLookupTableDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_cLookupTableDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_cLookupTableDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_cLookupTableDict() {
  TriggerDictionaryInitialization_cLookupTableDict_Impl();
}
