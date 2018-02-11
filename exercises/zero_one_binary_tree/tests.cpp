#include <iostream>
#include "zero_one_binary_tree.h"

int main() {
    CursorBinaryTree<int> B;
    ZeroOneBinaryTree Z;
    int root, left, right;
    B.ins_root();
    B.write(B.root(), 0);
    B.ins_left(B.root());
    B.write(B.left(B.root()), 1);
    B.ins_right(B.root());
    B.write(B.right(B.root()), 1);
    std::cout << Z.is_zero_one(B, B.root()) << std::endl;
    left = B.left(B.root());
    right = B.right(B.root());

    B.ins_left(left);
    B.ins_right(left);
    B.write(B.left(left), 0);
    B.write(B.right(left), 0);
    B.ins_left(right);
    B.ins_right(right);
    B.write(B.left(right), 0);
    B.write(B.right(right), 0);
    std::cout << Z.is_zero_one(B, B.root()) << std::endl;

    left = B.left(left);
    right = B.right(left);

    B.ins_left(left);
    B.write(B.left(left), 1);
    B.ins_right(left);
    B.write(B.right(left), 1);
    std::cout << Z.is_zero_one(B, B.root()) << std::endl;

    std::cout << "The number of nodes is: " << Z.controller_zero_nodes(B, B.root());
    std::cout << std::endl;

    return 0;
}
