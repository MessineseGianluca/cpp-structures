#include <iostream>
#include "tree_list/tree_list.h"
int main() {
    TreeList<char> my_tree_list;
    TreeList<char> my_tree2;
    TreeList<char>::node n, n2;
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

    my_tree_list.print();

    n = my_tree_list.root();
    n = my_tree_list.first_child(n);
    my_tree_list.remove_sub_tree(n);

    my_tree_list.print();
    std::cout << "The depth of the tree is: " << my_tree_list.depth(my_tree_list.root()) << std::endl;
    my_tree_list.preorder(my_tree_list.root());
    std::cout << std::endl;
    my_tree_list.postorder(my_tree_list.root());
    std::cout << std::endl;

    my_tree2.ins_root();
    my_tree2.write_node(my_tree2.root(),'z');

    my_tree2.ins_first(my_tree2.root(), 'f');
    my_tree2.ins_first(my_tree2.root(), 'h');

    n2 = my_tree2.root();
    n2 = my_tree2.first_child(n2);

    my_tree2.ins(n2, 'l');

    n2 = my_tree2.root();
    n2 = my_tree2.first_child(n2);
    my_tree2.ins_first(n2, 'k');
    my_tree2.ins_first(n2, 'u');
    n = my_tree_list.root();
    my_tree_list.ins_first_sub_tree(n, my_tree2);
    my_tree_list.print();

    n = my_tree_list.first_child(my_tree_list.root());
    n = my_tree_list.next_sibling(n);
    my_tree_list.ins_sub_tree(n, my_tree2);
    my_tree_list.print();

    my_tree_list.BFS(my_tree_list.root());
    std::cout << std::endl;
    int d = my_tree_list.width(my_tree_list.root());
    std::cout << "The max width of the tree is: " << d << std::endl;

    return 0;
}
