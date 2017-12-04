#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <iostream>

template <class T> class Stack {
public:
    typedef T value_type;
    Stack();
    Stack(int);
    ~Stack();
    void createStack();
    bool emptyStack() const;
    value_type readStack() const;
    void pop();
    void push(value_type);
private:
    value_type *elements_;
    int stack_dimension_;
    int head_;
};

template <class T> Stack<T>::Stack() {
    stack_dimension_ = 10;
    createStack();
}

template <class T> Stack<T>::Stack(int dimension) {
    stack_dimension_ = dimension;
    createStack();
}

template <class T> Stack<T>::~Stack() {
    delete[] elements_;
};

template <class T> void Stack<T>::createStack() {
    elements_ = new value_type[stack_dimension_]; // standard dimension of the stack
    head_ = 0;
}

template <class T> bool Stack<T>::emptyStack() const {
    return head_ == 0;
}

template <class T> typename Stack<T>::value_type Stack<T>::readStack() const {
    return elements_[head_ - 1];
}

template <class T> void Stack<T>::pop() {
    if (!emptyStack()) {
        head_ -= 1;
    } else {
        // EXCEPTION HERE
        std::cout << "No elements in the stack." << std::endl;
    }
}

template <class T> void Stack<T>::push(value_type element) {
    if (head_ == stack_dimension_) {
        // Exception here
        std::cout << "Max dimension of the stack reached." << std::endl;
    } else {
        elements_[head_] = element;
        head_++;
    }
}

#endif // ARRAY_STACK_H
