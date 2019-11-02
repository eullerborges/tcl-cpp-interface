#ifndef TCL_INTERP_H
#define TCL_INTERP_H

#include "defs.h"

#include <string>

#include "Object.h"

struct Tcl_Interp;

namespace tcl
{

class Interp
{
 public:
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

  //! @brief Returns the result options for the interpreter.
  //! @see Tcl_GetReturnOptions.
  Object getReturnOptions() const;

 private:
  Tcl_Interp* m_nativeRep {nullptr};
  CompletionCode m_lastCompletionCode {tcl::CompletionCode::OK};
};
}; // namespace tcl

#endif
