#include <iostream>
#include "cursor/cursor_binary_tree.h"
int main() {
    int root, pos, left, right;
    CursorBinaryTree<char> letters(21);
    letters.ins_root();
    root = letters.root();
    letters.write(root, 'a');
    letters.ins_left(root);
    letters.ins_right(root);
    pos = root;
    left = letters.left(pos);
    right = letters.right(pos);
    letters.write(left, 'b');
    letters.write(right, 'c');
    letters.ins_right(left);
    letters.write(letters.right(left), 'e');
    std::cout << letters;
    std::cout << "PREVISIT: ";
    letters.previsit(root);
    std::cout << std::endl << "SIMMETRIC VISIT: ";
    letters.simmetric_visit(root);
    std::cout << std::endl << "POSTVISIT: ";
    letters.postvisit(root);

    letters.erase(letters.left(root));
    std::cout << std::endl << letters;

    return 0;
}
