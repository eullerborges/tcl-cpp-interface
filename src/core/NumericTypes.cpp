#include "tcl++/core/NumericTypes.h"

#include <tcl.h>

#include <cassert>

using tcl::Numeric;

namespace {
template<class BaseType>
Tcl_Obj* instantiate(BaseType value);

template<> Tcl_Obj* instantiate<int>(int value) { return Tcl_NewIntObj(value); }
template<> Tcl_Obj* instantiate<long>(long value) { return Tcl_NewLongObj(value); }
template<> Tcl_Obj* instantiate<Tcl_WideInt>(Tcl_WideInt value) { return Tcl_NewWideIntObj(value); }
template<> Tcl_Obj* instantiate<bool>(bool value) { return Tcl_NewBooleanObj(value); }
template<> Tcl_Obj* instantiate<double>(double value) { return Tcl_NewDoubleObj(value); }

template <class BaseType>
int get(Tcl_Obj* nativeRep, BaseType& val);

template <> int get<int>(Tcl_Obj* nativeRep, int& val) { return Tcl_GetIntFromObj(nullptr, nativeRep, &val); }
template <> int get<long>(Tcl_Obj* nativeRep, long& val) { return Tcl_GetLongFromObj(nullptr, nativeRep, &val); }
template <> int get<Tcl_WideInt>(Tcl_Obj* nativeRep, Tcl_WideInt& val) { return Tcl_GetWideIntFromObj(nullptr, nativeRep, &val); }
template <> int get<bool>(Tcl_Obj* nativeRep, bool& val) { return Tcl_GetBooleanFromObj(nullptr, nativeRep, reinterpret_cast<int*>(&val)); }
template <> int get<double>(Tcl_Obj* nativeRep, double& val) { return Tcl_GetDoubleFromObj(nullptr, nativeRep, &val); }
}  // namespace

template<class BaseType>
Numeric<BaseType>::Numeric(BaseType value) : tcl::Object(instantiate<BaseType>(value)) {}

template <class BaseType>
Numeric<BaseType>::Numeric() : Numeric(BaseType{}){}

template <class BaseType>
BaseType Numeric<BaseType>::value() const
{
  BaseType val{};
  auto res = get(m_nativeRep, val);
  assert(res);
  return val;
}

namespace tcl {
// Forcing explicit instantiation
template class Numeric<int>;
template class Numeric<long>;
template class Numeric<Tcl_WideInt>;
template class Numeric<bool>;
template class Numeric<double>;
}
