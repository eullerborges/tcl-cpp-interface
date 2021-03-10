#include "tcl++/core/List.h"

#include "tcl++/core/Exception.h"

#include <tcl.h>

using tcl::List;

struct ConversionFailure : tcl::Exception {
  ConversionFailure() : tcl::Exception("could not convert object to list representation") {}
};

List::List() : tcl::Object(Tcl_NewListObj(0, nullptr)) {}

List& List::append(const Object& obj) {
  Tcl_ListObjAppendElement(nullptr, m_nativeRep, obj.getNativeRep());
  return *this;
}

bool List::splice(const List& obj) {
  return Tcl_ListObjAppendList(nullptr, m_nativeRep, obj.getNativeRep()) == TCL_OK;
}

std::size_t List::size() const {
  int sz;
  Tcl_ListObjLength(nullptr, m_nativeRep, &sz);
  return sz;
}

template <>
List tcl::Object::as() const {
  int sz;
  if (Tcl_ListObjLength(nullptr, m_nativeRep, &sz) != TCL_OK) {
    throw ConversionFailure();
  }
  return tcl::List(m_nativeRep);
}

