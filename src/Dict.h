#ifndef TCL_DICT_H
#define TCL_DICT_H

#include "Object.h"

#include <optional>

namespace tcl {

class Dict : public Object {
 public:
  using Object::Object;
  Dict();

  void put(const tcl::Object& key, const tcl::Object& value);

  template <class TclClass>
  std::optional<TclClass> get(const tcl::Object& key) const;

  //! Returns the current number of dictionary key-value pairs.
  std::size_t size() const;
};

};  // namespace tcl

#endif
