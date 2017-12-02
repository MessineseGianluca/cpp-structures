#ifndef LINKED_LINKED_LIST_H_
#define LINKED_LINKED_LIST_H_

#include "../linear_list.h"
#include <exception>

template< class T > class LinkedList;

class InvalidPosException: public std::exception {
    virtual const char* what() const throw() {
        return "This position doesn't belong to the list.";
    }
} inv_pos_ex;

template< class T > class Node {
	friend class LinkedList<T>;
private:
	T value_;
	Node<T> *prev_node_;
	Node<T> *next_node_;
	Node<T> *list_; // points to the list(sentinel) of his own in order to avoid
	                // conflict
public:
    /*
     * This method checks if a Node< T > belongs to a struct (list, stack, etc.)
     * This is useful for those methods of a struct that use positions to
     * access to the elements(nodes) of the struct: you have to check if a
     * position actually refers to a element of the struct or not.
     */
    bool belongs(const Node< T > *sentinel) const {
        return this->list_ == sentinel;
    }
};

template < class T > class LinkedList : public LinearList< T, Node<T>* > {
public:
    typedef typename LinearList< T, Node<T>* >::value_type value_type;
    typedef typename LinearList< T, Node<T>* >::position position;
	// constructor
	LinkedList();
	// copy constructor
	LinkedList(const LinkedList<T>& );
    // array constructor
    LinkedList(const value_type [], int);
    // destructor
	~LinkedList();

	// operators
	void create();
	bool empty() const;
	position begin() const;
	position last() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	value_type read(position) const;
	void write(const value_type &, position);
	void insert(const value_type &, position);
	void erase(position);
	int size() const {
		return length_;
	};

	// operator's overloading
	LinkedList<T> &operator = (const LinkedList<T> &); // the assignment operator
	bool operator == (const LinkedList<T> &) const; // tests two list for equality

 private:
	Node<T> *head_;
	int length_; // the length of the list
};

template < class T > LinkedList< T >::LinkedList() {
	head_ = new Node<T>;
    head_->next_node_ = head_;
    head_->prev_node_ = head_;
	head_->list_ = head_;
    length_ = 0;
}

template < class T >
LinkedList < T >::LinkedList(const LinkedList<T> &list_to_copy) {
	head_ = new Node<T>;
	head_->next_node_ = head_;
	head_->prev_node_ = head_;
	head_->list_ = head_;
    if (!list_to_copy.empty()) {
        position p = list_to_copy.last();
	    while(p != begin()) {
		    insert(list_to_copy.read(p), begin());
		    p = list_to_copy.previous(p);
	    }
    }
}

template< class T >
LinkedList< T >::LinkedList(const value_type a[], int dimension) {
    head_ = new Node<T>;
    head_->next_node_ = head_;
    head_->prev_node_ = head_;
    head_->list_ = head_;
    length_ = 0;
    for(int i = dimension - 1; i >= 0; i--) {
        this->insert(a[i], this->begin());
    }
}

template < class T > LinkedList < T >::~LinkedList() {
	while(!empty()) erase(begin());
	delete head_;
}

template < class T > void LinkedList< T >::create() {
	if (empty()) length_ = 0;
}

template < class T > bool LinkedList< T >::empty() const {
	if(this->head_->next_node_ == this->head_) return true;
	else return false;
}

template < class T >
typename LinkedList< T >::position LinkedList< T >::begin() const {
	return this->head_->next_node_;
}

template < class T >
typename LinkedList< T >::position LinkedList< T >::last() const {
	return this->head_->prev_node_;
}

template < class T > bool LinkedList< T >::end(position p) const {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        return p == this->head_;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T >
typename LinkedList< T >::position LinkedList< T >::next(position p) const {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        return p->next_node_;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T >
typename LinkedList< T >::position LinkedList< T >::previous(position p) const {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        if( p != this->head_ ) return p->prev_node_;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T >
typename LinkedList< T >::value_type LinkedList< T >::read(position p) const {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        if (!end(p)) return(p->value_);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T >
void LinkedList< T >::write(const value_type &v, position p) {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        if(!end(p)) p->value_ = v;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T >
void LinkedList< T >::insert(const value_type &v, position p) {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        position new_node = new Node<T>;
        new_node->value_ = v;
        new_node->list_ = this->head_;
        new_node->next_node_ = p;
        new_node->prev_node_ = p->prev_node_;
        p->prev_node_->next_node_ = new_node;
        p->prev_node_ = new_node;
        this->length_++;
    } catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template < class T > void LinkedList< T >::erase(position p) {
    try {
        if(!p->belongs(this->head_)) throw inv_pos_ex;
        if( !empty() && !end(p) ) {
            p->prev_node_->next_node_ = p->next_node_;
            p->next_node_->prev_node_ = p->prev_node_;
            this->length_--;
            delete p;
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

template< class T >
LinkedList<T> &LinkedList<T>::operator = (const LinkedList<T> &vl) {
    position new_node = this->head_->next_node_;
	position node_to_copy = vl.begin();
	if(&vl != this) {
		for(int i = 0; i < this->size(); i++) {
			new_node->value_ = node_to_copy->value_;
            new_node->list_ = this->head_;
			new_node = next(new_node);
			node_to_copy = vl.next(node_to_copy);
		}

		if(this->size() >= vl.size()) {
			while( !end(new_node) ) {
				new_node = next(new_node);
				erase(new_node->prev_node_);
			}
		} else {
			while( !vl.end(node_to_copy) ) {
				insert( node_to_copy->value_, new_node);
				node_to_copy = vl.next(node_to_copy);
			}
 		}
	}
	return *this;
}

template< class T >
bool LinkedList<T>::operator == (const LinkedList<T> &vl) const {
    bool equal = true;
	position list_pos = this->begin();
	position vl_pos = vl.begin();
    int i = 0;
	if(this->size() == vl.size()) {
		while( i < this->size() && equal ) {
            if(read(list_pos) != vl.read(vl_pos)) equal = false;
			list_pos = next(list_pos);
			vl_pos = vl.next(vl_pos);
			i++;
		}
	} else equal = false;
    return equal;
}

#endif /* LINKED_LINKED_LIST_H_ */
