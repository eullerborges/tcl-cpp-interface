#include "tcl++/core/Interp.h"

#define MAKE_EXTENSION(name, version, interp_name)                                                \
  static tcl::Interp* currentInterp = nullptr;                                                    \
                                                                                                  \
  void name##_Init(tcl::Interp& i);                                                               \
                                                                                                  \
  extern "C" int name##_Init(Tcl_Interp* pInterp) {                                               \
    if (Tcl_InitStubs(pInterp, TCL_VERSION, 0) == NULL) {                                         \
      return TCL_ERROR;                                                                           \
    }                                                                                             \
    /* changed this to check for an error - GPS */                                                \
    if (Tcl_PkgProvide(pInterp, #name, version) == TCL_ERROR) {                                   \
      return TCL_ERROR;                                                                           \
    }                                                                                             \
    currentInterp = new tcl::Interp(pInterp);                                                     \
    name##_Init(*currentInterp);                                                                  \
    return TCL_OK;                                                                                \
  }                                                                                               \
                                                                                                  \
  int name##_Unload(Tcl_Interp* pInterp, int flags) {                                             \
    if (currentInterp) {                                                                          \
      delete currentInterp;                                                                       \
      return TCL_OK;                                                                              \
    };                                                                                            \
    return TCL_ERROR;                                                                             \
  }                                                                                               \
                                                                                                  \
  int name##_SafeUnload(Tcl_Interp* pInterp, int flags) { return name##_Unload(pInterp, flags); } \
                                                                                                  \
  void name##_Init(tcl::Interp& interp_name)
