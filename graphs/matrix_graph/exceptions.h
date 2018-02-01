#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

struct InvalidNode : public std::invalid_argument {
    InvalidNode() : invalid_argument("Invalid parameter.") {};
};

#endif
