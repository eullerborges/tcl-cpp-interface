#include "tcl++/core/BaseCommand.h"
#include "tcl++/core/Dict.h"
#include "tcl++/core/List.h"
#include "tcl++/extend/defs.h"


class HelloCmd : public tcl::BaseCommand {
  int proc(tcl::Interp &interp, const std::vector<tcl::Object> &args) override {
    tcl::List l;
    for (const auto& arg : args) {
      l.append(arg.getStringRep());
    }
    interp.setResult(tcl::Dict().put("args", l));
    return TCL_OK;
  }
};

static int hello(ClientData cdata, Tcl_Interp *pInterp, int objc, Tcl_Obj *const objv[]) {
  tcl::Interp interp(pInterp);
  interp.setResult(tcl::List().append("test").append("setting").append(
      tcl::List().append("one").append("result")));
  return TCL_OK;
}

MAKE_EXTENSION(Math_example, "1.0", myinterp) {
  myinterp.setVar("test_var", tcl::String("test_value"));
  myinterp.registerCommand("hello_cmd", std::make_unique<HelloCmd>());
}
