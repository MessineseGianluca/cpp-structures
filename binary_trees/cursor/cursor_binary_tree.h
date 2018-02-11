/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
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
    node left(node) const;
    node right(node) const;
    bool left_empty(node) const;
    bool right_empty(node) const;
    //void constr(CursorBinaryTree<T>);
    void erase(node);
    T read(node) const;
    void write(node , value_type);
    void ins_root();
    void ins_left(node);
    void ins_right(node);

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
    space = new Cell[MAX_DIM_]; // creates an array of MAX_DIM_ cells
    create();
}

template <class T>
CursorBinaryTree<T>::CursorBinaryTree(int num_of_nodes_) {
    MAX_DIM_ = num_of_nodes_;
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
    /* A way to keep track of the next free node(position) in the array.
       By this way the nodes are introduced contiguously in the array, making
       very easy the insertion of the new nodes in the tree. (see ins_left,
       ins_root, ins_right methods).
    */
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
typename CursorBinaryTree<T>::node CursorBinaryTree<T>::left(node n) const {
    if (!left_empty(n))
        return(space[n].left);
    else
        return(n);
};

template <class T>
typename CursorBinaryTree<T>::node CursorBinaryTree<T>::right(node n) const {
    if (!right_empty(n))
        return (space[n].right);
    else
        return(n);
}

template <class T>
bool CursorBinaryTree<T>::left_empty(node n) const {
    return (space[n].left == NIL);
}

template <class T>
bool CursorBinaryTree<T>::right_empty(node n) const {
    return (space[n].right == NIL);
}

template <class T>
void CursorBinaryTree<T>::ins_root() {
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
void CursorBinaryTree<T>::ins_left(node n) {
  	if(start_ == NIL) throw EmptyTree();
  	if(n == NIL) throw NullNode();
  	if(space[n].left != NIL) throw NodeExists();
  	if(num_of_nodes_ >= MAX_DIM_) throw FullSize();
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
void CursorBinaryTree<T>::ins_right(node n) {
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
        if(!left_empty(n))
            erase(space[n].left);
        if(!right_empty(n))
            erase(space[n].right);
        if(n != start_) {
            node p = parent(n);
            if (space[p].left == n)
                space[p].left = NIL;
            else
                space[p].right = NIL;
        } else {
            start_ = NIL;
        }
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
    if (n != NIL) {
        space[n].value = a;
    } else {
        throw NullNode();
    }
}

#endif /* CURSOR_BINARY_TREE_H_ */
