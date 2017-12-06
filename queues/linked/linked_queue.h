#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

template< class T > class LinkedQueue;

template< class T > class Node {
	friend class LinkedQueue<T>;
private:
	T value_;
	Node<T> *prev_node_;
    Node<T> *next_node_;
};

template < class T > class LinkedQueue {
public:
    typedef T value_type;
    LinkedQueue();
    ~LinkedQueue();
    void create();
    bool empty() const;
    int size() { return length_; }
    void queue(const value_type &);
    void dequeue();
    value_type read() const; // read the first node in the queue
    void edit(const value_type &); // edit the first node in the queue
private:
    int length_;
    Node <T> *head_;
    Node <T> *tail_;
};

template < class T > LinkedQueue< T >::LinkedQueue() {
    head_ = new Node<T>;
    tail_ = new Node<T>;
    head_->next_node_ = tail_;
    tail_->prev_node_ = head_;
    length_ = 0;
}

template < class T > LinkedQueue< T >::~LinkedQueue() {
    while(!empty()) dequeue();
    delete head_;
    delete tail_;
}

template < class T > void LinkedQueue< T >::create() {
    if(empty()) length_ = 0;
}

template < class T > bool LinkedQueue< T >::empty() const {
    return length_ == 0;
}

template < class T >
typename LinkedQueue< T >::value_type LinkedQueue< T >::read() const {
    if(!empty()) return head_->next_node_->value_;
}

template < class T >
void LinkedQueue< T >::edit(const typename LinkedQueue< T >::value_type &val) {
    head_->next_node_->value_ = val;
}

template < class T >
void LinkedQueue< T >::queue(const typename LinkedQueue< T >::value_type &val) {
    Node< T > *new_node = new Node< T >;
    new_node->value_ = val;
    new_node->prev_node_ = tail_->prev_node_;
    tail_->prev_node_->next_node_ = new_node;
    tail_->prev_node_ = new_node;
    // first node in the queue needs to be linked to the head
    if(empty()) {
        head_->next_node_ = new_node;
    }
    length_++;
}

template < class T > void LinkedQueue< T >::dequeue() {
    if(!empty()) {
        Node<T> *temp_node = new Node< T >;
        temp_node = head_->next_node_;
        head_->next_node_ = (head_->next_node_)->next_node_;
        delete temp_node;
        length_--;
    }
}

#endif //LINKED_QUEUE_H
