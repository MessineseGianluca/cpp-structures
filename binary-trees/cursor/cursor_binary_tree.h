#ifndef CURSOR_BINARY_TREE_H_
#define CURSOR_BINARY_TREE_H_
#include "../binary_tree.h"
#include "exceptions.h"

template <class T> class CursorBinaryTree : public BinaryTree<T, int> {
    static const int NIL = -1;
public:
    typedef typename BinaryTree<T, int>::value_type value_type;
    typedef typename BinaryTree<T, int>::node node;
    struct cell {
        node parent;
        node left;
        node right;
        value_type value;
    };
    typedef struct cell Cell;
    // constructors and destructors
    CursorBinaryTree();
    CursorBinaryTree(int);
    ~CursorBinaryTree();

    // operators
    void create();
    bool empty() const;
    node root() const;
    node parent(node) const;
    node sx(node) const;
    node dx(node) const;
    bool sx_empty(node) const;
    bool dx_empty(node) const;
    //void costr(CursorBinaryTree<T>); A method for building a tree from the leaves to the root
    void erase(node);
    T read(node) const;
    void write(node , value_type);
    void ins_root(node);
    void ins_sx(node);
    void ins_dx(node);

private:
    int MAX_DIM_;
    Cell *space;
    int num_of_nodes_;
    node start_;
    node free_;
};

template <class T>
CursorBinaryTree<T>::CursorBinaryTree() {
    MAX_DIM_ = 100;
    space = new Cell[MAX_DIM_];
    create();
}

template <class T>
CursorBinaryTree<T>::CursorBinaryTree(int num_of_nodes_):MAX_DIM_(num_of_nodes_) {
    space = new Cell[num_of_nodes_];
    create();
}


template <class T>
CursorBinaryTree<T>::~CursorBinaryTree() {
    erase(start_);
    delete[] space;
}

template <class T>
void CursorBinaryTree<T>::create() {
    start_ = NIL;
    for (int i = 0; i < MAX_DIM_; i++) {
        space[i].left = (i + 1) % MAX_DIM_;
    }
    free_ = 0;
    num_of_nodes_ = 0;
}

template <class T>
bool CursorBinaryTree<T>::empty() const {
    return(num_of_nodes_ == 0);
}

template <class T>
typename CursorBinaryTree<T>::node CursorBinaryTree<T>::root() const {
    return(start_);
}

template <class T>
typename CursorBinaryTree<T>::node CursorBinaryTree<T>::parent(node n) const {
    if (n != start_)
        return (space[n].parent);
    else
        return(n);
}

template <class T>
typename CursorBinaryTree<T>::node CursorBinaryTree<T>::sx(node n) const {
    if (!sx_empty(n))
        return (space[n].left);
    else
        return(n);
};

template <class T>
typename     CursorBinaryTree<T>::node CursorBinaryTree<T>::dx(node n) const {
    if (!dx_empty(n))
        return (space[n].right);
    else
        return(n);
}

template <class T>
bool CursorBinaryTree<T>::sx_empty(CursorBinaryTree<T>::node n) const {
    return (space[n].left == NIL);
}

template <class T>
bool CursorBinaryTree<T>::dx_empty(CursorBinaryTree<T>::node n) const {
    return (space[n].right == NIL);
}

template <class T>
void CursorBinaryTree<T>::ins_root(CursorBinaryTree<T>::node n) {
    if (start_ == NIL) {
        start_ = free_;
        free_ = space[free_].left;
        space[start_].left = NIL;
        space[start_].right = NIL;
        num_of_nodes_++;
    }
    else throw RootExists();
}


template <class T>
void CursorBinaryTree<T>::ins_sx(node n) {
  	if(start_ == NIL)
  		  throw EmptyTree();
  	if(n == NIL)
  		  throw NullNode();
  	if(space[n].left != NIL)
  		  throw NodeExists();
  	if(num_of_nodes_ >= MAX_DIM_)
  		  throw FullSize();
    else {
        node q = free_;
        free_ = space[free_].left;
        space[n].left = q;
        space[q].left = NIL;
        space[q].parent = n;
        space[q].right = NIL;
        num_of_nodes_++;
    }
}

template <class T>
void CursorBinaryTree<T>::ins_dx(node n) {
  	if(start_ == NIL) throw EmptyTree();
  	if(n == NIL) throw NullNode();
  	if(space[n].right != NIL) throw NodeExists();
  	if(num_of_nodes_ >= MAX_DIM_) throw FullSize();
  	else {
        node q = free_;
        free_ = space[free_].left;
        space[n].right = q;
        space[q].parent = n;
        space[q].left = NIL;
        space[q].right = NIL;
        num_of_nodes_++;
    }
}

template <class T>
void CursorBinaryTree<T>::erase(node n) {
    if(n != NIL) {
        if(!sx_empty(n))
            erase(space[n].left);
        if(!dx_empty(n))
            erase(space[n].right);
        if(n != start_) {
            node p = parent(n);
            if (space[p].left == n)
                space[p].left = NIL;
            else
                space[p].right = NIL;
        }
        else start_ = NIL;
        num_of_nodes_--;
        space[n].left = free_;
        free_ = n;
    }
    else throw NullNode();
}

template <class T>
T CursorBinaryTree<T>::read(node n) const {
    if (n != NIL)
        return (space[n].value);
  	else throw NullNode();
}

template <class T>
void CursorBinaryTree<T>::write(node n, value_type a) {
    if (n != NIL)
        space[n].value = a;
	  else throw NullNode();
}

#endif /* CURSOR_BINARY_TREE_H_ */
