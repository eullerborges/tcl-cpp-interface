#ifndef TCL_BASECOMMAND_H
#define TCL_BASECOMMAND_H

#include "tcl++/core/Object.h"

#include <vector>

namespace tcl {
class Interp;

class BaseCommand {
 public:
  virtual int proc(Interp& interp, const std::vector<tcl::Object>& args) = 0;
};

}  // namespace tcl

#endif
