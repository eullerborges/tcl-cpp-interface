#ifndef TCL_OBJECT_H
#define TCL_OBJECT_H

#include <string>

struct Tcl_Obj;

namespace tcl {

class Interp;

/**
 * @brief Representation of a Tcl Object in C++.
 * This class provides the basic interface for managing a Tcl Object. All other
 * core Tcl object classes are therefore derived from this one.
 */
class Object {
 public:
  Object(Tcl_Obj* transferredObj);
  virtual ~Object();
  Object(const Object& other);
  Object(Object&& other);
  Object& operator=(const Object& other);
  Object& operator=(Object&& other);

  Tcl_Obj* getNativeRep() const { return m_nativeRep; }

  /**
   * @brief Converts this type to a derived Tcl class (like Int, String, List, etc.).
   * @throws tcl::Exception if the conversion fails.
   */
  template <class Derived, std::enable_if_t<std::is_base_of_v<Object, Derived>, int> = 0>
  Derived as();

  /**
   * @brief Returns the string representation of an object.
   * Every core Tcl object can be represented as a string. This method returns
   * the underlying string representation.
   * @note This will force the string representation regeneration if it is
   * invalid for this object, and thus this might cause shimmering.
   * @see Tcl C API's Tcl_GetStringFromObj
   */
  std::string getStringRep() const;

 protected:
  Object();
  void incrRefCount();
  void decrRefCount();

  Tcl_Obj* m_nativeRep;
};

};  // namespace tcl

#endif
