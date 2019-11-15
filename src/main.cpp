#include "tcl++/core/Dict.h"
#include "tcl++/core/Interp.h"
#include "tcl++/core/List.h"
#include "tcl++/core/String.h"
#include "tcl++/core/defs.h"

#include <cassert>
#include <iostream>

int main() {
  tcl::Interp interp;
  // auto res = interp.eval("info blupt");
  // auto res = interp.eval(tcl::String("argh"));
  // // assert(res == tcl::CompletionCode::OK);
  // std::cout << "Result: " << interp.getResult().getStringRep() << "\n";
  // std::cout << "Options: " << interp.getReturnOptions().getStringRep() << "\n";

  tcl::List l;
  tcl::List l2;
  l2.append(tcl::String("blupt")).append(tcl::String("blarg"));
  l.append(tcl::String("ble")).append(tcl::String("bla")).splice(l2);
  std::cout << "List: " << l.getStringRep() << ", size: " << l.size() << "\n";

  // tcl::Dict d;
  // d.put(tcl::String("potato"), tcl::String("head"));
  // d.put(tcl::String("oh god"), l);
  // std::cout << "Dict: " << d.getStringRep() << "\n";
  // std::cout << "Key: " << d.get<tcl::List>(tcl::String("oh god"))->getStringRep();

  return 0;
}
