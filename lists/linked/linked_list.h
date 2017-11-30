#ifndef LINKED_LINKED_LIST_H_
#define LINKED_LINKED_LIST_H_

template< class T > class LinkedList;

template< class T > class Node {
	friend class LinkedList<T>;
private:
	T value_;
	Node<T> *prev_node_;
	Node<T> *next_node_;
	Node<T> *list_; //points to the list(sentinel) of his own in order to avoid
	                //conflict
};
/*
// In order to avoid position conflict: "A next-position of a node in list A
// could point to a node which belongs to a different list B";
template <typename T> class Position {
friend class LinkedList<T>;
private:
	Node<T> *node; //points to the node of his own
	Node<T> *list; //points to the list(sentinel) of his own
};
*/
template < class T > class LinkedList : public LinearList< T, Node<T>* > {
public:
    typedef typename LinearList< T, Node<T>* >::value_type value_type;
    typedef typename LinearList< T, Node<T>* >::position position;
	// constructor
	LinkedList();
	// copy constructor
	LinkedList(const LinkedList<T>& );
	//distructor
	~LinkedList();

	// methods
	void create();
	bool empty() const;
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
	position last() const;
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void insert(const value_type &, position);
	void erase(position);
	int size() const {
		return length_;
	};
	// operators overloading
	LinkedList<T>& operator = (const LinkedList<T>&); // the assignment operator
	bool operator == (const LinkedList<T> &) const; // tests two list for equality

 private:
	Node<T> head_;
	int length_; // the length of the list
};

template < class T > LinkedList< T >::LinkedList() {
	head_ = new Node<T>;
    head_->next_node_ = head_;
    head_->prev_node_ = head_;
	head_->list = head_;
    length_ = 0;
}

template < class T > LinkedList < T >::LinkedList(const LinkedList<T> &list_to_copy) {
	head_ = new Node<T>;
	head_->next_node_ = head_;
	head_->prev_node_ = head_;
	head_->list = head_;
    if (!list_to_copy.empty()) {
        position p = list_to_copy.last();
	    while(p != begin()) {
		    insert(list_to_copy.read(p), begin());
		    p = list_to_copy.previous(p);
	    }
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

template < class T > position LinkedList< T >::begin() const {
	return this->head_->next_node_;
}

template < T > position LinkedList< T >::last() const {
	return this->head_->prev_node_;
}




#endif /* LINKED_LINKED_LIST_H_ */
