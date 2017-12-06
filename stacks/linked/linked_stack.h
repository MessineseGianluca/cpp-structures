#ifndef LINKED_STACK_H
#define LINKED_STACK_H

template< class T > class LinkedStack;

template< class T > class Node {
	friend class LinkedStack<T>;
private:
	T value_;
	Node<T> *prev_node_;
};

template < class T > class LinkedStack {
public:
    typedef T value_type;
    LinkedStack();
    ~LinkedStack();
    void create();
    bool empty() const;
    int size() { return length_; }
    void push(const value_type &);
    void pop();
    value_type read() const; // read node on the top_
    void edit(const value_type &); // edit node on the top
    //T headNode() { return this->head_->value_; }
private:
    int length_;
    Node < T > *head_;
};

template < class T > LinkedStack< T >::LinkedStack() {
    head_ = new Node<T>;
    head_->prev_node_ = head_;
    //head_->list_ = head_;
    length_ = 0;
}

template < class T > LinkedStack< T >::~LinkedStack() {
    while(!empty()) pop();
    delete head_;
}

template < class T > void LinkedStack< T >::create() {
    if(empty()) length_ = 0;
}

template < class T > bool LinkedStack< T >::empty() const {
    return length_ == 0;
}

template < class T >
typename LinkedStack< T >::value_type LinkedStack< T >::read() const {
    if(!empty()) return head_->prev_node_->value_;
}

template < class T >
void LinkedStack< T >::edit(const typename LinkedStack< T >::value_type &val) {
    head_->prev_node_->value_ = val;
}

template < class T >
void LinkedStack< T >::push(const typename LinkedStack< T >::value_type &val) {
    Node< T > *new_node = new Node< T >;
    new_node->value_ = val;
    new_node->prev_node_ = head_->prev_node_;
    head_->prev_node_ = new_node;
    length_++;
}

template < class T > void LinkedStack< T >::pop() {
    Node< T > *temp_node = new Node< T >;
    temp_node = head_->prev_node_;
    head_->prev_node_ = head_->prev_node_->prev_node_;
    delete temp_node;
    length_--;
}

#endif //LINKED_STACK_H
