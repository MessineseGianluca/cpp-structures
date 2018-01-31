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
  	TreeList() { create(); }
    // Implement destructor

    void create();
  	bool empty() const;
  	void ins_root();
  	node root() const;
  	node parent(node) const;
  	bool leaf(node) const;
  	node first_child(node) const;
  	bool last_sibling(node) const;
  	node next_sibling(node) const;
  	// To implement
  	//  void insFirstSubTree(node, TreeList &);
  	//	void insSubTree(node, TreeList &);
  	void remove_sub_tree(node);
  	void ins_first(node, item);
  	void ins(node, item);
  	void write_node(node, item);
  	item read_node(node) const;
  	void print() const;
 private:
  	Record nodes[MAX_NODES]; // array of parent nodess
  	node root_; // cursor to root element
    int num_of_nodes;
};


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
	  for (int i = 0; i < MAX_NODES; i++){
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
  	while (!nodes[p].childs.end(c))
  		  c = nodes[p].childs.next(c);
    // c is the last child of p
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
void TreeList<I>::remove_sub_tree(node n){
  	position_list c;
    node p;
    if(!leaf(n)){
        while(!nodes[n].childs.empty()){
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

#endif /* TREE_LIST_H */
