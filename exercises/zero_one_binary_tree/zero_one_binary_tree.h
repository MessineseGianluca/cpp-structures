/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
#include "../../binary_trees/cursor/cursor_binary_tree.h"

class ZeroOneBinaryTree {
public:
    typedef typename CursorBinaryTree<int>::node node;
    /* establishes whether the tree is a zero-one tree, which has the following properties:
     * 1) The root has value 0
     * 2) each node 0 has as children two nodes 1
     * 3) each node 1 has as children two nodes 0
     */
    bool is_zero_one(const CursorBinaryTree<int> &B, node n) const;
    /* Returns the number of 0 nodes in the tree */
    int controller_zero_nodes(const CursorBinaryTree<int> &B, node n) const;
private:
    void zero_nodes(const CursorBinaryTree<int> &B, node, int &) const;

};

bool ZeroOneBinaryTree::is_zero_one(const CursorBinaryTree<int> &B, node n) const {
    bool left_return, right_return;
    if(B.root() == n && B.read(n) != 0) {
        return false;
    }
    if(!B.leaf(n)) {
        if(!B.left_empty(n)) {
            left_return = is_zero_one(B, B.left(n));
        } else {
            return false;
        }
        if(!B.right_empty(n)) {
            right_return = is_zero_one(B, B.right(n));
        } else {
            return false;
        }
        if((B.read(n) == 0) && (B.read(B.parent(n)) == 1 || n == B.root()) && right_return && left_return) {
            return true;
        } else if((B.read(n) == 1 && B.read(B.parent(n)) == 0) && right_return && left_return) {
            return true;
        } else {
            return false;
        }
    } else if(B.root() == n) { // the root is 0 and is a leaf
        return true;
    } else {
        if((B.read(n) == 0 && B.read(B.parent(n)) == 1)) {
            return true;
        } else if((B.read(n) == 1 && B.read(B.parent(n)) == 0)) {
            return true;
        } else {
            return false;
        }
    }
}

int ZeroOneBinaryTree::controller_zero_nodes(const CursorBinaryTree<int> &B, node n) const {
    node r = B.root();
    if(is_zero_one(B, r)) {
        int counter = 0;
        zero_nodes(B, r, counter);
        return counter;
    } else {
        return 0;
    }
}

void ZeroOneBinaryTree::zero_nodes(const CursorBinaryTree<int> &B, node n, int &counter) const {
    if(B.read(n) == 0) {
        counter++;
    }
    if(!B.left_empty(n)) {
        zero_nodes(B, B.left(n), counter);
    }
    if(!B.right_empty(n)) {
        zero_nodes(B, B.right(n), counter);
    }
}
