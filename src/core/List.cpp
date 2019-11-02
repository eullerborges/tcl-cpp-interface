#include "tcl++/core/List.h"

#include "tcl.h"

using tcl::List;

List::List() : tcl::Object(Tcl_NewListObj(0, nullptr)) {}

List& List::append(const Object& obj) {
  Tcl_ListObjAppendElement(nullptr, m_nativeRep, obj.getNativeRep());
  return *this;
}

bool List::splice(const List& obj) {
  return Tcl_ListObjAppendList(nullptr, m_nativeRep, obj.getNativeRep()) ==
         TCL_OK;
}

std::size_t List::size() const
{
  int sz;
  Tcl_ListObjLength(nullptr, m_nativeRep, &sz);
  return sz;
}
