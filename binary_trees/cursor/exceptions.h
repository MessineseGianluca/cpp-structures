#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

struct NullNode : public std::invalid_argument {
    NullNode() : invalid_argument("Null parameter.") {};
};

struct FullSize : public std::invalid_argument {
    FullSize() : invalid_argument("Max dimension reached.") {};
};

struct RootExists : public std::domain_error {
    RootExists() : domain_error("Root already exists.") {};
};

struct EmptyTree : public std::domain_error {
    EmptyTree() : domain_error("The tree is empty.") {};
};

struct NodeExists : public std::domain_error {
    NodeExists() : domain_error("Node already exists.") {};
};

#endif
