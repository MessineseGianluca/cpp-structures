#include <iostream>
#include "util_n_tree.h"

int main() {
    TreeList<char> my_tree_list;
    TreeList<char>::node n;
    my_tree_list.ins_root();
    my_tree_list.write_node(my_tree_list.root(),'a');

    my_tree_list.ins_first(my_tree_list.root(), 'b');
    my_tree_list.ins_first(my_tree_list.root(), 'c');

    n = my_tree_list.root();
    n = my_tree_list.first_child(n);

    my_tree_list.ins(n, 'd');

    n = my_tree_list.root();
    n = my_tree_list.first_child(n);
    my_tree_list.ins_first(n, 'e');
    my_tree_list.ins_first(n, 'f');

    my_tree_list.print();

    UtilNTree<char> u;
    std::cout << "The num of leaves in the tree is: " << u.n_leaf(my_tree_list);
    std::cout << std::endl;
    int level = 2;
    std::cout << "The num of nodes in the level " << level << " is: " << u.n_level(my_tree_list, level);
    std::cout << std::endl;

    return 0;
}
