/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <stdexcept>

struct InvalidNode : public std::invalid_argument {
    InvalidNode() : invalid_argument("Inexistent node.") {};
};

struct EdgeAlreadyExists : public std::invalid_argument {
    EdgeAlreadyExists(): invalid_argument("This edge already exists.") {};
};

struct GraphIsNotConnected : public std::invalid_argument {
    GraphIsNotConnected(): invalid_argument("The graph is not connected!") {};
};

#endif
