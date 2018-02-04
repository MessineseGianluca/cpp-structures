#ifndef TREE_H
#define TREE_H
#include "../queues/linked/linked_queue.h"

template<class I, class N>
class Tree {
public:
  	typedef I item; // type of the atom
  	typedef N node; // position of the atom
  	virtual void create() = 0;
  	virtual bool empty() const = 0;
  	virtual void ins_root() = 0;
  	virtual node root() const = 0;
  	virtual node parent(node) const = 0;
  	virtual bool leaf(node) const = 0;
  	virtual node first_child(node) const = 0;
  	virtual bool last_sibling(node) const = 0;
  	virtual node next_sibling(node) const = 0;
  	virtual void remove_sub_tree(node) = 0;
  	virtual void write_node(node, item) = 0;
  	virtual item read_node(node) const = 0;
    virtual int get_num_of_nodes() const = 0;
    virtual bool search(const item) const = 0;
  	void BFS(node) const;
  	void preorder(node) const;
  	void postorder(node) const;
    int depth(node) const;
    // int width() const = 0;
};

template<class I, class N> int Tree<I, N>::depth(node n) const {
    node v;
    int max, c, max_depth;
    if(leaf(n)) max_depth = 0;
    else {
        v = first_child(n);
        max = depth(v);
        std::cout << last_sibling(v) << std::endl;
        while(!last_sibling(v)) {
            v = next_sibling(v);
            std::cout << read_node(v);
            std::cout << last_sibling(v);
            c = depth(v);
            if(max < c) {
                max = c;
            }
        }
        max_depth = max + 1;
    }
    return max_depth;
}

template<class I, class N> void Tree<I, N>::preorder(node n) const {
    node c;
    std::cout << read_node(n) << " ";
    if(!leaf(n)) {
        c = first_child(n);
        while(!last_sibling(c)) {
            preorder(c);
            c = next_sibling(c);
        }
        preorder(c);
    }
}

template<class I, class N> void Tree<I, N>::postorder(node n) const {
    node c;
    if(!leaf(n)) {
        c = first_child(n);
        while(!last_sibling(c)) {
            postorder(c);
            c = next_sibling(c);
        }
        postorder(c);
    }
    std::cout << read_node(n) << " ";
}


template<class I, class N> void Tree<I, N>::BFS(node n) const {
    node c;
    LinkedQueue<node> q;
    q.queue(n);
    while(!q.empty()) {
        c = q.read();
        std::cout << read_node(c);
        q.dequeue();
        if(!leaf(c)) {
            c = first_child(c);
            while(!last_sibling(c)) {
                q.queue(c);
                c = next_sibling(c);
            }
            q.queue(c);
        }
    }
}


#endif /* TREE_H */
