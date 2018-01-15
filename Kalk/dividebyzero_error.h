#ifndef DIVIDEBYZERO_ERROR_H
#define DIVIDEBYZERO_ERROR_H

#include<stdexcept>
#include<string>

using std::string;
using std::runtime_error;
using std::exception;

class dividebyzero_error : public runtime_error
{
public:
    explicit dividebyzero_error(const string&);
};

#endif // DIVIDEBYZERO_ERROR_H
