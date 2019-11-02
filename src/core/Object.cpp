#include "tcl++/core/Object.h"

#include "tcl.h"

#include <cassert>

using tcl::Object;

Object::Object() : Object(Tcl_NewObj()) {}

Object::Object(Tcl_Obj* transferredObj) : m_nativeRep(transferredObj) {
  incrRefCount();
}

Object::~Object() { decrRefCount(); }

Object::Object(const Object& other)
    : m_nativeRep(Tcl_DuplicateObj(other.m_nativeRep)) {
  incrRefCount();
}

Object& Object::operator=(const Object& other) { return *this; }

void Object::incrRefCount() {
  if (m_nativeRep) Tcl_IncrRefCount(m_nativeRep);
}
void Object::decrRefCount() {
  if (m_nativeRep) Tcl_DecrRefCount(m_nativeRep);
}

std::string Object::getStringRep() const {
  int length;
  const char* rep = Tcl_GetStringFromObj(m_nativeRep, &length);
  assert(rep);
  return {rep, static_cast<std::size_t>(length)};
}
