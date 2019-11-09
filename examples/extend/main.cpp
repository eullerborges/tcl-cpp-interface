#include "tcl++/extend/defs.h"
#include "tcl.h"

#include "tcl++/core/List.h"

static int hello(ClientData cdata, Tcl_Interp *pInterp, int objc,
                     Tcl_Obj *const objv[]) {
  tcl::Interp interp(pInterp);
  interp.setResult(tcl::List().append("test").append("setting").append(tcl::List().append("one").append("result")));
  return TCL_OK;
}

MAKE_EXTENSION(Math_example, myinterp) {
  myinterp.setVar("test_var", tcl::String("test_value"));
  Tcl_CreateObjCommand(myinterp.getNativeRep(), "hello", hello, NULL, NULL);
}
