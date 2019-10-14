#ifndef TCL_LIST_H
#define TCL_LIST_H

#include "Object.h"

namespace tcl {

class List : public Object {
 public:
  using Object::Object;
  List();

  //! Appends a given Tcl object to this list and returns reference to self.
  List& append(const Object& obj);
  //! Splices all elements from another list into this one (by copy).
  bool splice(const List& l);
  //! Returns the current list's size.
  std::size_t size() const;
};

};  // namespace tcl

#endif
