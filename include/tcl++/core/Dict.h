#ifndef TCL_DICT_H
#define TCL_DICT_H

#include "Object.h"
#include "String.h"

#include <optional>

namespace tcl {

class Dict : public Object {
 public:
  using Object::Object;
  Dict();

  Dict &put(const tcl::Object &key, const tcl::Object &value);
  Dict &put(const tcl::String &key, const tcl::Object &value) {
    return put(static_cast<const Object &>(key), value);
  }
  //! Splices all elements from another list into this one (by copy).

  template <class TclClass>
  std::optional<TclClass> get(const tcl::Object &key) const;

  //! Returns the current number of dictionary key-value pairs.
  std::size_t size() const;
};

};  // namespace tcl

#endif
