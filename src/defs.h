#ifndef TCL_DEFS_H
#define TCL_DEFS_H

namespace tcl {
enum class CompletionCode { OK = 0, ERROR, RETURN, BREAK, CONTINUE };

struct Result {
  CompletionCode completionCode;
};

}; // namespace tcl

#endif
