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

  /**
   * @brief Inserts the value for a given key in the dictionary.
   * @param key Key for which to insert the value.
   * @param value Value to insert.
   * @return Reference to this dictionary.
   */
  Dict &put(const tcl::Object &key, const tcl::Object &value);
  //! Convenience overloaod for inserting with string keys
  Dict &put(const tcl::String &key, const tcl::Object &value) {
    return put(static_cast<const Object &>(key), value);
  }

  /**
   * @brief Retrieves the value for a key in the dictionary, if it exists.
   * @param key Key for which to retrieve the value.
   * @return The value for the key if existing, empty optional otherwise.
   */
  template <class TclClass = Object>
  std::optional<TclClass> get(const tcl::Object &key) const {
    auto val = internalGet(key);
    return val ? tcl::Object(val).as<TclClass>() : std::optional<TclClass>();
  }

  //! Returns the current number of dictionary key-value pairs.
  std::size_t size() const;

 private:
  Tcl_Obj *internalGet(const tcl::Object &key) const;
};

};  // namespace tcl

#endif
