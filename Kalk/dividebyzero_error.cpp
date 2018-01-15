#include "dividebyzero_error.h"

using std::string;
using std::runtime_error;

dividebyzero_error::dividebyzero_error(const string& what_arg) :
    runtime_error(what_arg)
{}

