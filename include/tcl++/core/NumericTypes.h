#ifndef TCL_NUMERIC_H
#define TCL_NUMERIC_H

#include "Object.h"

namespace tcl {

template <class BaseType> class Numeric;

// Avalailable Tcl integer types
using Int = Numeric<int>;
using Long = Numeric<long>;
using Boolean = Numeric<bool>;
using Double = Numeric<double>;

/**
 * @brief Basic interface for numeric types in Tcl
 * Numeric types in Tcl all share the same sort of interface for access. This
 * template provides the high-level abstraction of all those Tcl C interfaces.
 */
template <class BaseType>
class Numeric : public Object {
 public:
  using Object::Object;

  //! Constructs an empty Tcl int.
  Numeric();

  /**
   * @brief Constructs a Tcl integer.
   * @param value Value to initialize the integer with.
   */
  Numeric(BaseType value);

  BaseType value() const;

  explicit operator BaseType() const { return value(); }
};

};  // namespace tcl

#endif
