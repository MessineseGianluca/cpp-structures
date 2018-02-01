#include <iostream>
#include "tree_list/tree_list.h"
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
    std::cout << "The depth of the tree is: " << my_tree_list.depth(my_tree_list.root()) << std::endl;
    my_tree_list.preorder(my_tree_list.root());
    std::cout << std::endl;
    my_tree_list.postorder(my_tree_list.root());
    std::cout << std::endl;
    n = my_tree_list.root();
    n = my_tree_list.first_child(n);
    my_tree_list.remove_sub_tree(n);

    my_tree_list.print();
    std::cout << "The depth of the tree is: " << my_tree_list.depth(my_tree_list.root()) << std::endl;
    my_tree_list.preorder(my_tree_list.root());
    std::cout << std::endl;
    my_tree_list.postorder(my_tree_list.root());
    std::cout << std::endl;

    return 0;
}
