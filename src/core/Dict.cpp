#include "tcl++/core/Dict.h"

#include "tcl++/core/Exception.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"

#include <tcl.h>

using tcl::Dict;

Dict::Dict() : tcl::Object(Tcl_NewDictObj()) {}

std::size_t Dict::size() const {
  int sz;
  Tcl_DictObjSize(nullptr, m_nativeRep, &sz);
  return sz;
}

Dict& Dict::put(const tcl::Object& key, const tcl::Object& value) {
  Tcl_DictObjPut(nullptr, m_nativeRep, key.getNativeRep(), value.getNativeRep());
  return *this;
}

template <class TclClass>
std::optional<TclClass> Dict::get(const tcl::Object& key) const {
  Tcl_Obj* valptr;
  Tcl_DictObjGet(nullptr, m_nativeRep, key.getNativeRep(), &valptr);
  return TclClass(valptr);
}

template std::optional<tcl::String> Dict::get(const tcl::Object& key) const;
template std::optional<tcl::List> Dict::get(const tcl::Object& key) const;
template std::optional<tcl::Dict> Dict::get(const tcl::Object& key) const;

template <>
tcl::Dict tcl::Object::as() {
  int sz;
  if (Tcl_DictObjSize(nullptr, m_nativeRep, &sz) != TCL_OK) {
    throw tcl::Exception("could not convert object to list representation");
  }
  return tcl::Dict(m_nativeRep);
}
