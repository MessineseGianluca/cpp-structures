/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
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
    int width(node) const;
private:
    void previsit_width(node, int &, int *) const;
};

template<class I, class N> int Tree<I, N>::depth(node n) const {
    node v;
    int max, c, max_depth;
    if(leaf(n)) max_depth = 0;
    else {
        v = first_child(n);
        max = depth(v);
        while(!last_sibling(v)) {
            v = next_sibling(v);
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

template <class I, class N> int Tree<I, N>::width(node n) const {
    int d = depth(n) + 1;
    int levels[d]; // array wich contains the num of nodes for each level
    int max;
    int current = 0;
    int i;
    // init each element to 0
    for(i = 0; i < d; i++) {
        levels[i] = 0;
    }
    previsit_width(n, current, levels);
    max = levels[0];
    // search the max
    for(i = 1; i < d; i++) {
      if(levels[i] > max) {
          max = levels[i];
      }
    }
    return max;
}

template <class I, class N>
void Tree<I, N>::previsit_width(node n, int &current, int *levels) const {
    node c;
    levels[current]++;
    if(!leaf(n)) {
        current++;
        c = first_child(n);
        while(!last_sibling(c)) {
            previsit_width(c, current, levels);
            c = next_sibling(c);
        }
        previsit_width(c, current, levels);
        current--;
    }
}


#endif /* TREE_H */
