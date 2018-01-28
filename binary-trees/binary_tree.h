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
    virtual node left(node) const = 0;
    virtual node right(node) const = 0;
    virtual bool left_empty(node) const = 0;
    virtual bool right_empty(node) const = 0;

    //virtual void constr(BinaryTree<T, N>);
    virtual void erase(node) = 0;

    virtual T read(node) const = 0;
    virtual void write(node, value_type) = 0;

    virtual void ins_root() = 0;
    virtual void ins_left(node) = 0;
    virtual void ins_right(node) = 0;

    void previsit(node);
    void simmetric_visit(node);
    void postvisit(node);
    void print() const;
private:
    void print_sub_tree(const node) const;
};

template <class T, class N>
void BinaryTree<T, N>::previsit(node n) {
    std::cout << read(n) << " ";
    if(!left_empty(n))
        previsit(left(n));
    if(!right_empty(n))
        previsit(right(n));
}

template <class T, class N>
void BinaryTree<T, N>::simmetric_visit(node n) {
    if(!left_empty(n))
        simmetric_visit(left(n));
    std::cout << read(n) << " ";
    if(!right_empty(n))
        simmetric_visit(right(n));
}

template <class T, class N>
void BinaryTree<T, N>::postvisit(node n) {
    if(!left_empty(n))
        postvisit(left(n));
    if(!right_empty(n))
        postvisit(right(n));
    std::cout << read(n) << " ";

}



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
    if (!left_empty(n))
    	  print_sub_tree(left(n));
    else std::cout << "NIL";
    std::cout << ", ";
    if (!right_empty(n))
    	print_sub_tree(right(n));
    else std::cout << "NIL";
    std::cout << " ]";
}

template<class T, class N>
std::ostream& operator<<(std::ostream& out, const BinaryTree<T, N>& t) {
    t.print();
    return out;
}

#endif /*BINARY_TREE_H_*/
