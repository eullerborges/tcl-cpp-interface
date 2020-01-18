#ifndef TCL_BASECOMMAND_H
#define TCL_BASECOMMAND_H

#include "Object.h"
#include "defs.h"
#include "tcl++/util/span.h"

#include <vector>

namespace tcl {
class Interp;

class BaseCommand {
 public:
  virtual ~BaseCommand() = default;
  virtual CompletionCode proc(Interp& interp, tcb::span<tcl::Object> args) = 0;
};

}  // namespace tcl

#endif
