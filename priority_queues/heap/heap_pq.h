#ifndef _CODAPO_H_
#define _CODAP_H_
#include "assert.h"

template< class T > class Heap_Priority_Queue {
public:
    typedef T elem_type;
    Heap_Priority_Queue();
    Heap_Priority_Queue(int);
    ~Heap_Priority_Queue();

    void create();
    void insert(elem_type);
    elem_type min();
    void delete_min();

private:
    int dimension_;
    elem_type *heap;
    int last;
    void fixUp();
    void fixDown(int, int);
};

template< class T >
Heap_Priority_Queue < T >::Heap_Priority_Queue ():dimension_(100) {
    heap = new elem_type[dimension_];
    create();
};

template< class T >
Heap_Priority_Queue < T >::Heap_Priority_Queue (int maxN):dimension_(maxN) {
    heap = new elem_type[dimension_];
    create ();
};

template< class T > Heap_Priority_Queue< T >::~Heap_Priority_Queue() {
    delete[] heap;
};

template< class T > void Heap_Priority_Queue< T >::create() {
    last = 0;
};

template< class T > void Heap_Priority_Queue < T >::insert(elem_type e) {
    assert(last < dimension_);
    heap[++last - 1] = e; //pre increment
    fixUp();
};

template< class T > typename Heap_Priority_Queue < T >::elem_type Heap_Priority_Queue < T >::min() {
    assert(last != 0); //empty queue
    return(heap[0]);
};

template< class T > void Heap_Priority_Queue < T >::delete_min() {
    assert (last != 0);
    heap[0] = heap[last - 1];
    last--;
    fixDown (1, last);
};

template< class T > void Heap_Priority_Queue < T >::fixUp() {
    int k = last;
    while (k > 1 && heap[k - 1] < heap[k / 2 - 1]) {
        elem_type tmp;
        // swap
        tmp = heap[k - 1];
        heap[k - 1] = heap[k / 2 - 1];
        heap[k / 2 - 1] = tmp;
        k = k / 2; // k becomes the father
    }
}

template< class T > void Heap_Priority_Queue < T >::fixDown(int k, int N) {
    bool swap = true;
    while (k <= N / 2 && swap) {
        int j = 2 * k;
        elem_type tmp;
        if (j < N && heap[j - 1] > heap[j])
  				  j++;
        if (swap = (heap[j - 1] < heap[k - 1])) { // if right(left) child < father
            // swap
    				tmp = heap[k - 1];
    				heap[k - 1] = heap[j - 1];
    				heap[j - 1] = tmp;
            // k becomes the child(left or right)
    				k = j;
  			}
    }
};


#endif /* _CODAP_H_ */
