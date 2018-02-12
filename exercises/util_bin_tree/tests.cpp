#include <iostream>
#include "util_bin_tree.h"

int main() {

    CursorBinaryTree<char> T(21);
    UtilBinTree<char> U;
    CursorBinaryTree<char>::node root;
    CursorBinaryTree<char>::node left;
    CursorBinaryTree<char>::node right;
    T.ins_root();
    T.write(T.root(), 'a');
    T.ins_left(T.root());
    T.write(T.left(T.root()), 'b');
    T.ins_right(T.root());
    T.write(T.right(T.root()), 'c');
    left = T.left(T.root());
    right = T.right(T.root());
    T.ins_left(left);
    T.ins_right(left);
    T.write(T.left(left), 'd');
    T.write(T.right(left), 'e');
    T.ins_left(right);
    T.ins_right(right);
    T.write(T.left(right), 'f');
    T.write(T.right(right), 'g');
    left = T.left(left);
    right = T.right(left);
    T.ins_left(left);
    T.write(T.left(left),'h');
    T.ins_right(left);
    T.write(T.right(left), 'i');
    std::cout << T.depth(T.root()) << std::endl;
    int k = 3;
    std::cout << "The number of leaves is: " << U.n_leaf(T) << std::endl;
    std::cout << "The number of nodes in the level " << k << " is: ";
    std::cout << U.n_level(T, k) << std::endl;

    return 0;
}
