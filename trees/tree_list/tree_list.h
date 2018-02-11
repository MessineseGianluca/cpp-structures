#ifndef TREE_LIST_H
#define TREE_LIST_H
#include "../tree.h"
#include "../../lists/array/array_list.h"
#define MAX_NODES 100

template<class I>
class TreeList : public Tree<I, int> {
public:
    typedef I item;
    typedef int node;
    typedef ArrayList<int>::position position_list;
    struct Record {
        item e;
        bool used;
        ArrayList<int> childs;
    };

    // constructors and destructors
    TreeList() {
        nodes = new Record[MAX_NODES];
        create();
    }
    ~TreeList();
    void create();
    bool empty() const;
    void ins_root();
    node root() const;
    node parent(node) const;
    bool leaf(node) const;
    node first_child(node) const;
    bool last_sibling(node) const;
    node next_sibling(node) const;
    void ins_first_sub_tree(node &, TreeList &);
    void ins_sub_tree(node &, TreeList &);
    void remove_sub_tree(node);
    void ins_first(node, item);
    void ins_last(node, item);
    void ins(node, item);
    void write_node(node, item);
    item read_node(node) const;
    void print() const;
    int get_num_of_nodes() const {
        return num_of_nodes;
    }
    bool search(const item) const;
 private:
    void preorder_ins_first(node, node , TreeList &);
    void preorder_ins(node, node , TreeList &);
    Record *nodes; // array of parent nodes
    node root_; // cursor to root element
    int num_of_nodes;
};

template <class I>
TreeList<I>::~TreeList() {
    delete[] nodes;
}

template <class I>
void TreeList<I>::print() const {
    std::cout << "\n{";
    for(int i = 0; i < MAX_NODES; i++){
    if(nodes[i].used == true) {
        std::cout << "\n  " << read_node(i) << ":  ";
            if(!leaf(i)) {
                position_list child = nodes[i].childs.begin();
                while(!nodes[i].childs.end(child)) {
                    std::cout << read_node(nodes[i].childs.read(child)) << " ";
                    child = nodes[i].childs.next(child);
                }
            }
        }
    }
    std::cout << "\n}\n";
}

template <class I>
void TreeList<I>::create() {
    num_of_nodes = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        nodes[i].used = false;
        nodes[i].childs.create();
    }
}

template <class I>
bool TreeList<I>::empty() const {
    return(num_of_nodes == 0);
}

template <class I>
void TreeList<I>::ins_root() {
    if (empty()) {
        root_ = 0;
        nodes[root_].used = true;
        num_of_nodes++;
    }
}

template <class I>
typename TreeList<I>::node TreeList<I>::root() const {
    return root_;
}

template <class I>
typename TreeList<I>::node TreeList<I>::parent(node n) const {
    position_list child;
    int p;
    bool found = false;
    for(int i = 0; i < MAX_NODES; i++) {
        if(!nodes[i].childs.empty()) {
            child = nodes[i].childs.begin();
            while(!nodes[i].childs.end(child) && !found) {
                if(nodes[i].childs.read(child) == n) {
                    found = true;
                    p = i;
                 }
                 child = nodes[i].childs.next(child);
            }
            if(found) return(i);
        }
    }
    /* if(!found) throw exception */
}

template <class I>
bool TreeList<I>::leaf(node n) const {
    return(nodes[n].childs.empty());
}

template <class I>
typename TreeList<I>::node TreeList<I>::first_child(node n) const {
    if(!leaf(n)) {
        return(nodes[n].childs.read(nodes[n].childs.begin()));
    }
}

template <class I>
bool TreeList<I>::last_sibling(node n) const {
    position_list c;
    node p = parent(n);
    c = nodes[p].childs.begin();
    while(!nodes[p].childs.end(c)) {
        c = nodes[p].childs.next(c);
    }
    c = nodes[p].childs.previous(c);
    return (n == nodes[p].childs.read(c));
}

template <class I>
typename TreeList<I>::node TreeList<I>::next_sibling(node n) const {
    position_list c;
    if(!last_sibling(n)) {
        node p = parent(n);
        c = nodes[p].childs.begin();
        while(!nodes[p].childs.end(c)) {
            if(nodes[p].childs.read(c) == n)
              return(nodes[p].childs.read(nodes[p].childs.next(c)));
            c = nodes[p].childs.next(c);
        }
    }
    /* else throw exception */
}

template <class I>
void TreeList<I>::ins_first_sub_tree(node &n, TreeList &B) {
    if(num_of_nodes + B.get_num_of_nodes() <= MAX_NODES) {
        B.preorder_ins_first(B.root(), n, *this);
    }
}


template <class I>
void TreeList<I>::preorder_ins_first(node n, node in_node, TreeList &InTree) {
    node c;
    item node_value = read_node(n);
    if(n == root()) {
        InTree.ins_first(in_node, node_value);
        in_node = InTree.first_child(in_node);
    } else {
        InTree.ins_last(in_node, node_value);
        if(n == first_child(parent(n)) && !last_sibling(n)) { //if it's the first child
            // go down
            in_node = InTree.first_child(in_node);
        } else if(last_sibling(n)) {
            // go up
            in_node = InTree.parent(in_node);
        }
    }
    if(!leaf(n)) {
        c = first_child(n);
        while(!last_sibling(c)) {
            preorder_ins_first(c, in_node, InTree);
            c = next_sibling(c);
        }
        preorder_ins_first(c, in_node, InTree);
    }
}
template <class I>
void TreeList<I>::ins_sub_tree(node &n, TreeList &B) {
    if(num_of_nodes + B.get_num_of_nodes() <= MAX_NODES) {
        B.preorder_ins(B.root(), n, *this);
    }
}

template <class I>
void TreeList<I>::preorder_ins(node n, node in_node, TreeList &InTree) {
    node c;
    item node_value = read_node(n);
    if(n == root()) {
        InTree.ins(in_node, node_value);
        in_node = InTree.next_sibling(in_node);
    } else {
        InTree.ins_last(in_node, node_value);
        if(n == first_child(parent(n)) && !last_sibling(n)) { //if it's the first child
            // go down
            in_node = InTree.first_child(in_node);
        } else if(last_sibling(n)) {
            // go up
            in_node = InTree.parent(in_node);
        }
    }
    if(!leaf(n)) {
        c = first_child(n);
        while(!last_sibling(c)) {
            preorder_ins(c, in_node, InTree);
            c = next_sibling(c);
        }
        preorder_ins(c, in_node, InTree);
    }
}



// insert a node as first_child of n
template <class I>
void TreeList<I>::ins_first(node n, item el){
    int k = -1;
    // search for a free position in nodes[]
    do {
        k++;
    } while(k < MAX_NODES && nodes[k].used == true);
    if(k < MAX_NODES) {
        nodes[k].used = true;
        nodes[k].e = el;
        nodes[n].childs.insert(k, nodes[n].childs.begin());
    }
}

template <class I>
void TreeList<I>::ins_last(node n, item el) {
    int k = -1;
    // search for a free position in nodes[]
    do {
        k++;
    } while(k < MAX_NODES && nodes[k].used == true);
    if(k < MAX_NODES) {
        nodes[k].used = true;
        nodes[k].e = el;
        nodes[n].childs.insert_last(k);
    }
}

// insert a node as a sibling of n
template <class I>
void TreeList<I>::ins(node n, item el) {
    int k = -1;
    position_list child;
    node p;
    // search for a free position in nodes[]
    do {
        k++;
    } while(k < MAX_NODES && nodes[k].used == true);
    if(k < MAX_NODES) {
        nodes[k].used = true;
        nodes[k].e = el;
        p = parent(n);
        child = nodes[p].childs.begin();
        bool found = false;
        /* find the position of n in nodes[p] (parent of n)*/
        while (!nodes[p].childs.end(child) && !found) {
            if (nodes[p].childs.read(child) == n) {
                found = true;
            }
            child = nodes[p].childs.next(child);
        }
        /* insert the new node position into nodes[p] (next to n position) */
        nodes[p].childs.insert(k, child);
    }
}

template <class I>
void TreeList<I>::remove_sub_tree(node n) {
    position_list c;
    node p;
    if(!leaf(n)) {
        while(!nodes[n].childs.empty()) {
            remove_sub_tree(nodes[n].childs.read(nodes[n].childs.begin()));
        }
    }
    p = parent(n);
    c = nodes[p].childs.begin();
    /* find the position of n in nodes.childs */
    while(nodes[p].childs.read(c) != n) {
        c = nodes[p].childs.next(c);
    }
    nodes[p].childs.erase(c);
    nodes[n].used = false;
}

template <class I>
void TreeList<I>::write_node(node n, item el) {
    nodes[n].e = el;
}

template <class I>
typename TreeList<I>::item TreeList<I>::read_node(node n) const {
    return(nodes[n].e);
}

template <class I>
bool TreeList<I>::search(const item el) const {
    node p;
    int i = 0;
    bool found = false;
    while(i < MAX_NODES && !found) {
        if(nodes[i].used == true && nodes[i].e == el) {
            found = true;
        }
        i++;
    }
    return p;
}

#endif /* TREE_LIST_H */
