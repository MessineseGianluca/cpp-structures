#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

struct InvalidNode : public std::invalid_argument {
    InvalidNode() : invalid_argument("Inexistent node.") {};
};

struct EdgeAlreadyExists : public std::invalid_argument {
    EdgeAlreadyExists(): invalid_argument("This edge already exists.") {};
};


#endif