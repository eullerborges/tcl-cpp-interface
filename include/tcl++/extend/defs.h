#include "tcl++/core/Interp.h"

#define MAKE_EXTENSION(name, interp_name)           \
  void name##_Init(tcl::Interp& i);                 \
                                                    \
  extern "C" int name##_Init(Tcl_Interp* pInterp) { \
    tcl::Interp interp(pInterp);                    \
    name##_Init(interp);                            \
    return 0;                                       \
  }                                                 \
                                                    \
  void name##_Init(tcl::Interp& interp_name)
