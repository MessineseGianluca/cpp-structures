#ifndef LINEAR_LIST_H_
#define LINEAR_LIST_H_

#include <iostream>

template < class T, class P > class LinearList {
public:
	typedef T value_type; // the type of object T, stored in the list
	typedef P position; // the type of the position P (pointer or integer)

	/****************************** VIRTUAL METHODS ***********************************/
	virtual void create() = 0;
	virtual bool empty() const = 0; // true if the list's size is 0
	virtual value_type read(position) const = 0; // reads the object of position
	virtual void write(const value_type &x, position p) = 0; // write x at position p
	virtual position begin() const = 0;  // returns a position pointing to the beginning of the list
	virtual bool end(position) const = 0; // verify whether a position refers to the last element of the list
	virtual position next(position) const = 0; // returns the next position
	virtual position previous(position) const = 0; // return the previous position
	virtual void insert(const value_type &, position) = 0; // insert an element
	virtual void erase(position pos) = 0; // erases the element at position pos
    virtual int size() const = 0; //implementation here is not efficient(see derivated classes)
	/***************************** SERVICE METHODS **************************************/

	//friend ostream& operator << <T,P>(ostream&, const Linear_list<T,P>&);
	void invert();
	bool is_palindrome() const;
};

/*template< class T, class P > int LinearList<T, P>::size() const {
    P i = begin();
    int counter = 0;
    while( !end(i) ) {
       	counter++;
       	i = next(i);
    }
    return counter;
}*/

template< class T, class P > void LinearList<T, P>::invert() {
	if( !empty() ) {
		T temp_node;
		P pos_first = begin(); //position of the first item
		int length = size();
		P cont = pos_first;
		P pos_last; //position of the last item

		while( !end(cont) ) {
			pos_last = cont;
            cont = next(cont);
		}

		int num_of_loops = length / 2;

		/*Inverts first with last, etc..*/
        for(int i = 0; i < num_of_loops; i++) {
            temp_node = read(pos_last);
            write(read(pos_first), pos_last);
            write(temp_node, pos_first);
            pos_first = next(pos_first);
            pos_last = previous(pos_last);
	    }
    }
}

template < class T, class P > bool LinearList<T, P>::is_palindrome() const {
    bool pal = true;
    P pos_first = begin();
    P cont = pos_first;
	int length = size();
    P pos_last;
    while( !end(cont) ) {
	    pos_last = cont;
        cont = next(cont);
	}
    int mid = length / 2 ;
    if( !empty() ) {
        int i = 0;
    	while( pal && i < mid ) {
    		if(read(pos_first) == read(pos_last)) {
        	    pos_first = next(pos_first);
        	    pos_last = previous(pos_last);
    		} else {
    			pal = false;
    		}
    		i++;
        }
    }
    return pal;
}

#endif /* LINEAR_LIST_H_ */
