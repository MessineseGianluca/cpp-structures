#include <iostream>
#include "array/array_stack.h"
#include "linked/linked_stack.h"

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


    /**************************** LinkedStack ********************************/
    LinkedStack<char> link_stack;
    link_stack.push('a');
    link_stack.pop();
    if(link_stack.empty()) std::cout << "empty!" << std::endl;
    std::cout << link_stack.read() << std::endl;
    link_stack.push('a');
    link_stack.push('b');
    link_stack.push('c');
    link_stack.push('d');
    std::cout << link_stack.read() << std::endl;
    link_stack.pop();
    std::cout << link_stack.read() << std::endl;

    LinkedStack< LinkedStack<char> > stack_of_stacks;
    /*
    stack_of_stacks.push(link_stack);
    link_stack.push('d');
    stack_of_stacks.push(link_stack);
    LinkedStack<char> t = stack_of_stacks.headNode();
    std::cout << t.read();
    */
    return 0;

}
