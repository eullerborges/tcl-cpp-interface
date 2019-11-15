#ifndef TCL_STRING_H
#define TCL_STRING_H

#include "Object.h"

#include <string>

namespace tcl {

class String : public Object {
 public:
  using Object::Object;

  //! Constructs an empty Tcl string.
  String();

  /**
   * @brief Constructs a Tcl string with a copy of a character string.
   * @param cstr Character string used to initialize the Tcl String.
   * @param length Size of the character string used in the initialization. The
   * string is assumed to be null terminated if -1.
   */
  String(const char* cstr, std::size_t length = -1);

  /**
   * @brief Constructs a Tcl string with a copy of an std::string.
   * @param str String used to initialize the Tcl String.
   */
  String(const std::string& str);
};

};  // namespace tcl

#endif
