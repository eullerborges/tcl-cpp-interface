#include "tcl++/core/Dict.h"
#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/NumericTypes.h"
#include "tcl++/core/String.h"
#include "tcl++/core/WideInt.h"
#include "tcl++/core/defs.h"

#include <cassert>
#include <iostream>

int main() {
  tcl::Interp interp;

  tcl::List l;
  tcl::List l2;
  l2.append(tcl::String("blupt")).append(tcl::String("blarg"));
  l.append(tcl::String("ble")).append(tcl::String("bla")).splice(l2);
  std::cout << "List: " << l.getStringRep() << ", size: " << l.size() << "\n";

  tcl::Dict d;
  d.put(tcl::String("key"), tcl::String("value"));
  d.put(tcl::String("with spaces"), l);
  d.put(tcl::String("myint"), tcl::Int(42));
  d.put(tcl::String("mylong"), tcl::Long(long(1)<< 62));
  d.put(tcl::String("mywide"), tcl::WideInt(Tcl_WideInt(20)));
  d.put(tcl::String("mybool"), tcl::Boolean(true));
  d.put(tcl::String("mydouble"), tcl::Double(3.14));
  std::cout << "Dict: " << d.getStringRep() << "\n";

  return 0;
}
