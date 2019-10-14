#ifndef TCL_STRING_H
#define TCL_STRING_H

#include "Object.h"

#include <string>

namespace tcl {

class String : public Object {
 public:
  using Object::Object;
  String(const char* cstr, std::size_t length = -1);
  explicit String(const std::string& str);
};

};  // namespace tcl

#endif
