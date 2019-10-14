#include "String.h"

#include "tcl.h"

using tcl::String;

String::String(const char* cstr, std::size_t length)
    : tcl::Object(Tcl_NewStringObj(cstr, length)) {}

String::String(const std::string& str) : String(str.c_str(), str.length()) {}
