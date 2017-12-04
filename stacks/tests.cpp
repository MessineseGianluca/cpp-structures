#include <iostream>
#include "array/array_stack.h"

int main() {
    Stack<int> my_stack(5);

    std::cout << "I'm adding 5 to the stack." << std::endl;
    my_stack.push(5);
    std::cout << my_stack.readStack() << std::endl;

    std::cout << "I'm adding 6 to the stack." << std::endl;
    my_stack.push(6);
    std::cout << my_stack.readStack() << std::endl;

    std::cout << "pop()" << std::endl;
    my_stack.pop();
    std::cout << my_stack.readStack() << std::endl;

    my_stack.push(6);
    my_stack.push(6);
    my_stack.push(6);
    my_stack.push(6);
    my_stack.push(6);

    my_stack.pop();
    my_stack.pop();
    my_stack.pop();
    my_stack.pop();
    my_stack.pop();
    my_stack.pop();

    Stack<char> my_stack2("ciao", 4);
    std::cout << my_stack2.readStack() << std::endl;

    return 0;
}
