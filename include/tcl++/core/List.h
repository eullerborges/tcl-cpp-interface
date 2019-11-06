#ifndef TCL_LIST_H
#define TCL_LIST_H

#include "Object.h"
#include "String.h"

namespace tcl {

class List : public Object {
 public:
  using Object::Object;
  List();

  //! Appends a given Tcl object to this list and returns reference to self.
  List& append(const Object& obj);
  //! Convenience method to ease up the addition of strings.
  List& append(const String& obj) { return append(static_cast<const Object&>(obj)); }
  //! Splices all elements from another list into this one (by copy).
  bool splice(const List& l);
  //! Returns the current list's size.
  std::size_t size() const;
};

};  // namespace tcl

#endif
