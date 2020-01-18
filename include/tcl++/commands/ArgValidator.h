#ifndef TCL_ARGVALIDATOR_H
#define TCL_ARGVALIDATOR_H

#include "tcl++/core/Interp.h"
#include "tcl++/core/Object.h"

namespace tcl {

class ArgValidator {
 public:
  virtual void validate(Interp& interp, Object& obj) = 0;
  bool validated() { return m_validated; }

  void validateArg(Interp& interp, Object& obj) {
    validate(interp, obj);
    m_validated = true;
  }

  bool m_validated;
};

};  // namespace tcl

#endif
