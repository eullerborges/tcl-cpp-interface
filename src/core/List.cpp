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

template <bool Const>
typename List::base_iterator<Const>::pointer List::base_iterator<Const>::operator->() const {
  Tcl_Obj* objPtr;
  // NOTE: another option is to use Tcl_ListObjGetElements and store it in the
  // iterator. That seems to not be 100% safe though, as in the implementation
  // Tcl mentions that any call to the list functions might invalidate the returned array.
  if (Tcl_ListObjIndex(nullptr, m_parent->getNativeRep(), m_idx, &objPtr) != TCL_OK) {
    throw ConversionFailure();
  }
  auto& mutableValue = const_cast<std::optional<Object>&>(m_value);
  mutableValue = std::optional<Object>(objPtr);
  return &*mutableValue;
}

template List::iterator::pointer List::iterator::operator->() const;
template List::const_iterator::pointer List::const_iterator::operator->() const;
