#ifndef LINKED_LINKED_LIST_H_
#define LINKED_LINKED_LIST_H_

template< class T > class LinkedList;

template< class T > class Node {
private:
	T _value;
	Node<T> *prev_node;
	Node<T> *next_node;
};

// In order to avoid position conflict: "A next-position of a node in list A
// could point to a node which belongs to a different list B";
template <typename T> class Position {
friend class LinkedList<T>;
private:
	Node<T> *node; //points to the node of his own
	Node<T> *list; //points to the list(sentinel) of his own
};

template < class T > class LinkedList : public LinearList< T, Position<T> > {
public:
    typedef typename LinearList< T, Position<T> >::value_type value_type;
    typedef typename LinearList< T, Position<T> >::position position;
	// constructor
	LinkedList();
	LinkedList(int);
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
	Position<T> head_;
	int length_; // the length of the list
};


#endif /* LINKED_LINKED_LIST_H_ */
