#ifndef TCL_WIDEINT_H
#define TCL_WIDEINT_H

#include "NumericTypes.h"
#include <tcl.h>

namespace tcl {
// Tcl's wide int type. This requires the definition on tcl.h and is thus kept in a separate file.
using WideInt = Numeric<Tcl_WideInt>;
};  // namespace tcl

#endif
