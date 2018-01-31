#ifndef TREE_H
#define TREE_H
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
  	// To implement!
  	// virtual void ins_first_sub_tree(node, Tree &) = 0;
  	// virtual void ins_sub_tree(node, Tree &) = 0;
  	virtual void remove_sub_tree(node) = 0;
  	virtual void write_node(node, item) = 0;
  	virtual item read_node(node) const = 0;
  	// void BFS(node) const = 0;
  	// void preorder(node) const = 0;
  	// void postorder(node) const = 0;
    // node research(item) const = 0;
    // int depth() const = 0;
    // int width() const = 0;
};

#endif /* TREE_H */
