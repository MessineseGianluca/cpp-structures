/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */

#include "../../binary_trees/cursor/cursor_binary_tree.h"

template<class I>
class UtilBinTree {
public:
    typedef typename CursorBinaryTree<I>::node node;
    UtilBinTree() {};
    ~UtilBinTree() {};
    /* returns the number of leaves in the tree*/
    int n_leaf(const CursorBinaryTree<I> &T) const;
    /* return the number of nodes in the level k of the tree */
    int n_level(const CursorBinaryTree<I> &T, int k) const;
private:
    void count_leaves(node, const CursorBinaryTree<I> &, int &) const;
    void count_level(const CursorBinaryTree<I> &, node, int, int &, int &) const;
};

template<class I>
int UtilBinTree<I>::n_leaf(const CursorBinaryTree<I> &T) const {
    int count = 0;
    count_leaves(T.root(), T, count);
    return count;
}

template<class I>
void UtilBinTree<I>::count_leaves(node n, const CursorBinaryTree<I> &T, int &counter) const {
    node c;
    if(T.leaf(n)) {
        counter++;
    } else {
        if(!T.left_empty(n)) {
            c = T.left(n);
            count_leaves(c, T, counter);
        }
        if(!T.right_empty(n)) {
            c = T.right(n);
            count_leaves(c, T, counter);
        }

    }
}


template<class I>
int UtilBinTree<I>::n_level(const CursorBinaryTree<I> &T, int k) const {
    int level = 0;
    int counter = 0;
    node r = T.root();
    if(k <= T.depth(T.root())) {
        count_level(T, r, k, level, counter);
    }
    return counter;
}

template<class I>
void UtilBinTree<I>::count_level(const CursorBinaryTree<I> &T, node n, int k, int &level, int &counter) const {
    if(level == k) {
        counter++;
    }
    if(!T.left_empty(n)) {
        level++;
        count_level(T, T.left(n), k, level, counter);
        level--;
    }
    if(!T.right_empty(n)) {
        level++;
        count_level(T, T.right(n), k, level, counter);
        level--;
    }
}
