#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <iostream>
#include <exception>

class NoElementsException: public std::exception {
    virtual const char* what() const throw() {
        return "No elements in the stack!";
    }
} no_el_ex;

class MaxDimensionReachedException: public std::exception {
    virtual const char* what() const throw() {
        return "Max dimension of the stack has been reached!";
    }
} max_dim_ex;

template <class T> class Stack {
public:
    typedef T value_type;
    Stack();
    Stack(int);
    // array constructor
    Stack(const value_type [], int);
    ~Stack(); //destructor
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

template <class T> Stack<T>::Stack(const value_type a[], int dimension) {
    stack_dimension_ = dimension;
    createStack();
    int i = 0;
    while(i < dimension) {
        push(a[i]);
        i++;
    }
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
    try {
        if(emptyStack()) throw no_el_ex;
        // in case of no exception
        head_ -= 1; // no need to delete[] the element from the stack, because
                    // it will be overwritten
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template <class T> void Stack<T>::push(value_type element) {
    try {
        if(head_ == stack_dimension_) throw max_dim_ex;
        // in case of no exception
        elements_[head_] = element;
        head_++;
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

#endif // ARRAY_STACK_H
