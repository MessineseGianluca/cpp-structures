#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_
#include <iostream>

template <class T, class N> class BinaryTree {
public:
    // types
    typedef T value_type;
    typedef N node;
    // operators
    virtual void create() = 0;
    virtual bool empty() const =  0;
    virtual node root() const = 0;
    virtual node parent(node) const =  0;
    virtual node sx(node) const = 0;
    virtual node dx(node) const = 0;
    virtual bool sx_empty(node) const = 0;
    virtual bool dx_empty(node) const = 0;

    //virtual void costr(BinaryTree<T, N>);
    virtual void erase(node) = 0;

    virtual T read(node) const = 0;
    virtual void write(node, value_type) = 0;

    virtual void ins_root(node) = 0;
    virtual void ins_sx(node) = 0;
    virtual void ins_dx(node) = 0;

    //virtual void previsit(node);
    //virtual void invisita(node);
    //virtual void postvisit(node);

    void print() const;

private:
    void print_sub_tree(const node) const;
};

template <class T, class N>
void BinaryTree<T, N>::print() const{
	  if (!empty())
		    print_sub_tree(root());
	  else
		    std::cout << "[]" << std::endl;
	  std::cout << std::endl;
}

template <class T, class N>
void BinaryTree<T, N>::print_sub_tree(const node n) const {
    std::cout << "[" << read(n) << ", ";
    if (!sx_empty(n))
    	  print_sub_tree(sx(n));
    else std::cout << "NIL";
    std::cout << ", ";
    if (!dx_empty(n))
    	print_sub_tree(dx(n));
    else std::cout << "NIL";
    std::cout << " ]";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const BinaryTree<T, N>& t) {
    t.print();
    return out;
}

#endif /*BINARY_TREE_H_*/
