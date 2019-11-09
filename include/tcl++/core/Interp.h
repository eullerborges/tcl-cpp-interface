#ifndef TCL_INTERP_H
#define TCL_INTERP_H

#include "defs.h"

#include <string>

#include "Object.h"
#include "String.h"

struct Tcl_Interp;

namespace tcl
{

class Interp
{
 public:
  /**
   * Provides an interface wrapping the behaviour of an existing Tcl
   * interpreter
   * @param interp Intepreter to wrap.
   */
  explicit Interp(Tcl_Interp* interp);

  //! Instantiates a new Tcl interpreter
  Interp();
  ~Interp();

  /**
   * @brief Evaluates a script in the interpreter in the format of a string.
   * @param script Script to evaluate
   * @param global_context Whether to evaluate in a global context.
   * @sa Tcl C API's Tcl_EvalEx
   */
  CompletionCode eval(const Object& script, bool global_context = false);

  //! Overload for evaluating a string script without compiling.
  CompletionCode eval(const std::string& script, bool global_context = false);

  /**
   * @brief Returns the result of the last evaluation as a value.
   */
  Object getResult() const;

  /**
   * @brief Sets the interpreter result to a given Tcl Object.
   * @param obj Object to set the interpreter result to.
   */
  void setResult(const Object& obj);

  /**
   * @brief Sets a variable on the intepreter.
   * @param name Name of the variable to set.
   * @param optArrayElement If name refers to an array, the name of the array element (index) to set.
   * @param value Value of the variable created/modified.
   * @return true iff the operation succeeded.
   */
  bool setVar(const tcl::String &name, const tcl::Object &value,
              const tcl::String *optArrayElement = nullptr);

  //! @brief Returns the result options for the interpreter.
  //! @see Tcl_GetReturnOptions.
  Object getReturnOptions() const;

  Tcl_Interp *getNativeRep() const { return m_nativeRep; }

 private:
  Tcl_Interp* m_nativeRep {nullptr};
  bool m_owning;
  CompletionCode m_lastCompletionCode {tcl::CompletionCode::OK};
};
}; // namespace tcl

#endif
