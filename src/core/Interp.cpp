#include "tcl++/core/Interp.h"

#include <tcl.h>

using tcl::Interp;

namespace {
tcl::CompletionCode toCompletionCode(int code) { return static_cast<tcl::CompletionCode>(code); }
}  // namespace

Interp::Interp(Tcl_Interp* interp) : m_nativeRep{interp}, m_owning(false) {}

Interp::Interp() : m_nativeRep{Tcl_CreateInterp()}, m_owning(true) {}

Interp::~Interp() {
  if (m_owning) Tcl_DeleteInterp(m_nativeRep);
}

tcl::CompletionCode Interp::eval(const tcl::Object& cmd, bool global_context) {
  m_lastCompletionCode = toCompletionCode(
      Tcl_EvalObjEx(m_nativeRep, cmd.getNativeRep(), global_context ? TCL_EVAL_GLOBAL : 0));
  return m_lastCompletionCode;
}

tcl::CompletionCode Interp::eval(const std::string& cmd, bool global_context) {
  m_lastCompletionCode = toCompletionCode(
      Tcl_EvalEx(m_nativeRep, cmd.c_str(), cmd.size(), global_context ? TCL_EVAL_GLOBAL : 0));
  return m_lastCompletionCode;
}

tcl::Object Interp::getResult() const { return Tcl_GetObjResult(m_nativeRep); }

tcl::Object Interp::getReturnOptions() const {
  return Tcl_GetReturnOptions(m_nativeRep, static_cast<int>(m_lastCompletionCode));
}

void Interp::setResult(const tcl::Object& obj) {
  Tcl_SetObjResult(m_nativeRep, obj.getNativeRep());
}

bool Interp::setVar(const tcl::String& name, const tcl::Object& value,
                    const tcl::String* optArrayElement) {
  auto* arrayElement = optArrayElement ? optArrayElement->getNativeRep() : nullptr;
  return Tcl_ObjSetVar2(m_nativeRep, name.getNativeRep(), arrayElement, value.getNativeRep(), 0) !=
         NULL;
}
