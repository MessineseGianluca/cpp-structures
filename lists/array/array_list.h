#ifndef ARRAY_ARRAY_LIST_H_
#define ARRAY_ARRAY_LIST_H_

#include "../linear_list.h"

template < class T > class ArrayList : public LinearList<T, int> {
public:
    typedef typename LinearList<T, int>::value_type value_type;
	typedef typename LinearList<T, int>::position position;

	// constructor
	ArrayList();
	ArrayList(int);
	// copy constructor
	ArrayList(const ArrayList<T>&);

    // array constructor
	ArrayList(const value_type [], int);

	// destructor
	~ArrayList();

	// operators
	void create();
	bool empty() const;
	value_type read(position) const;
	void write(const value_type &, position);
	position begin() const;
    int size() const {
        return length_;
    }
	bool end(position) const;
	position next(position) const;
	position previous(position) const;
	void insert(const value_type &, position);
	void erase(position);

	// operator's overloading
	ArrayList<T> &operator = (const ArrayList<T>&); // the assignment operator
	bool operator == (const ArrayList<T>&) const; // tests two list for equality

private:
	void change_dimension_(T*& , int , int ); //array doubling
	value_type* elements_;
	int length_; // the length of the list
	int array_dimension_; // array's dimension
};

/******************************* CONSTRUCTORS *****************************/
template < class T > ArrayList< T >::ArrayList() {
	array_dimension_ = 10;
    this->create();

}

template< class T > ArrayList< T >::ArrayList(int dim){
	array_dimension_ = dim;
	this->create();
}


template< class T >
ArrayList< T >::ArrayList(const value_type a[], int dimension) {
    array_dimension_ = dimension;
    this->create();
    for(int i = 1; i <= dimension; i++) {
        this->insert(a[i - 1], i);
	}
}


/* Copy constructor handles the copy of the object.
 * This constructor is called, for example, when an object is passed for
 * value to a function or when a function return an object
 */
template< class T > ArrayList< T >::ArrayList(const ArrayList<T>& List) {
	this->array_dimension_ = List.array_dimension_;
	this->length_ = List.length_;
	this->elements_ = new T[array_dimension_];
	for (int i = 0; i < List.array_dimension_; i++)
		this->elements_[i] = List.elements_[i];
}

// destructor
template< class T > ArrayList< T >::~ArrayList() {
	delete elements_;
}

/******************************* OPERATORS ********************************/
template< class T > void ArrayList< T >::create() {
	this->elements_ = new T[array_dimension_];
	this->length_ = 0;
}

template< class T > bool ArrayList< T >::empty() const {
    return(length_ == 0);
}

template< class T >
typename ArrayList< T >::position ArrayList< T >::begin() const {
	return 1;
}

template< class T >
typename ArrayList< T >::position ArrayList< T >::next(position p) const {
	if ((0 < p) && (p < length_ + 1)) // precondiction
		return(p + 1);
	else
		return p;
}

template< class T >
typename ArrayList< T >::position ArrayList< T >::previous(position p) const {
	if ( (1 < p) && (p < length_ + 1)) // precondiction
		return(p - 1);
	else
		return p;
}

template< class T > bool ArrayList< T >::end(position p) const {
	if ( (0 < p) && (p <= length_ + 1)) // precondiction
		return( p == length_ + 1 );
	else
		return false;
}

template< class T >
typename ArrayList< T >::value_type ArrayList< T >::read(position p) const {
	if ( (0 < p) && (p < length_ + 1)) // precondiction
		return( elements_[p - 1] );
}

template< class T >
void ArrayList< T >::write(const value_type &a, position p) {
  if ( (0 < p) && (p < length_ + 1)) // precondiction
      elements_[p - 1] = a;
}

template< class T >
void ArrayList< T >::insert(const value_type &a, position p) {
    if (length_ == array_dimension_) {
        change_dimension_(elements_, array_dimension_, array_dimension_ * 2);
        array_dimension_ = array_dimension_ * 2;
    }
    if ( (0 < p) && (p <= length_ + 1)) { // precondiction
    	for (int i = length_; i >= p; i--)
			elements_[i] = elements_[i - 1];
		elements_[p - 1] = a;
		length_++;
	}
}

template< class T > void ArrayList< T >::erase(position p) {
	if ( (0 < p) && ( p < length_ + 1)) { // precondiction
		if ( !empty() ) {
			for (int i = p - 1; i < (length_ - 1); i++)
				elements_[i] = elements_[i + 1];
			length_--;
		}
	}
}

template< class T > void ArrayList< T >
::change_dimension_(T*& a, int old_dimension_, int new_dimension_) {
	T* temp = new T[new_dimension_];
	int number;
	if (old_dimension_ < new_dimension_)
		number = old_dimension_;
	else
		number = new_dimension_;
	for (int i = 0; i < number; i++)
		temp[i] = a[i];
	delete [] a;
	a = temp;
}

/* assignment operator */
template< class T >
ArrayList<T> &ArrayList<T>::operator = (const ArrayList<T> &vl) {
	if (!(this == &vl)) {   // pay attention to auto-assignments: l = l
		this->array_dimension_ = vl.array_dimension_;
		this->length_ = vl.length_;
		delete this->elements_;
		this->elements_ = new T[array_dimension_];
		for (int i = 0; i < vl.array_dimension_; i++)
			this->elements_[i] = vl.elements_[i];
	}
	return *this;
}

/* equality operator */
template< class T >
bool ArrayList<T>::operator == (const ArrayList<T> &vl) const {
	if (vl.length_ != this->length_)
		return false;
	for (int i = 0; i < this->array_dimension_; i++)
		if (this->elements_[i] != vl.elements_[i])
			return false;
	return true;
}

#endif /* ARRAY_ARRAY_LIST_H_ */
