#ifndef TCL_INTERP_H
#define TCL_INTERP_H

#include "BaseCommand.h"
#include "Object.h"
#include "String.h"
#include "defs.h"

#include <memory>
#include <string>
#include <unordered_map>

struct Tcl_Interp;

namespace tcl {

class Interp {
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
   * @param optArrayElement If name refers to an array, the name of the array element (index) to
   * set.
   * @param value Value of the variable created/modified.
   * @return true iff the operation succeeded.
   */
  bool setVar(const tcl::String& name, const tcl::Object& value,
              const tcl::String* optArrayElement = nullptr);

  //! @brief Returns the result options for the interpreter.
  //! @see Tcl_GetReturnOptions.
  Object getReturnOptions() const;

  Tcl_Interp* getNativeRep() const { return m_nativeRep; }

  /**
   * @brief Registers a new command on the interpreter.
   * @param cmdName Name of the command to register
   * @param command Object with the command definition.
   * @return Whether the command was successfully registered.
   */
  bool registerCommand(const std::string& cmdName, std::unique_ptr<BaseCommand>&& command);

  /**
   * @brief Unregisters a command from the interpreter.
   * @param cmdName Name of the command to unregister
   * @return Whether the command was successfully unregistered.
   */
  bool unregisterCommand(const std::string& cmdName);

  /**
   * @return Returns the object related to the command implementation associated with a command
   * name.
   * @param cmdName Name of the command for which to retrieve the implementation.
   */
  BaseCommand& getCommand(const std::string& cmdName) { return *m_commands.at(cmdName); };

 private:
  Tcl_Interp* m_nativeRep{nullptr};
  bool m_owning;
  CompletionCode m_lastCompletionCode{tcl::CompletionCode::OK};
  std::unordered_map<std::string, std::unique_ptr<BaseCommand>> m_commands;
};
};  // namespace tcl

#endif
