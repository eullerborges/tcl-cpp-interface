#include "tcl++/core/Object.h"

#include "tcl.h"

#include <cassert>
#include <stdexcept>

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

Object::Object(Object&& other)
  : m_nativeRep(other.m_nativeRep)
{
  other.m_nativeRep = nullptr;
}

Object& Object::operator=(const Object& other) {
  decrRefCount();
  m_nativeRep = Tcl_DuplicateObj(other.m_nativeRep);
  incrRefCount();
  return *this;
}

Object &Object::operator=(Object &&other) {
  std::swap(m_nativeRep, other.m_nativeRep);
  return *this;
}

void Object::incrRefCount() {
  if (m_nativeRep) Tcl_IncrRefCount(m_nativeRep);
}
void Object::decrRefCount() {
  if (m_nativeRep) Tcl_DecrRefCount(m_nativeRep);
}

std::string Object::getStringRep() const {
  if (!m_nativeRep) {
    throw std::runtime_error("String representation requested for uninitialized object");
  }
  int length;
  const char* rep = Tcl_GetStringFromObj(m_nativeRep, &length);
  assert(rep);
  return {rep, static_cast<std::size_t>(length)};
}
