#ifndef GRAPH_H
#define GRAPH_H

#include "../lists/array/array_list.h"

template<class W, class N>
class Edge_ {
public:
  	N node1;
  	N node2;
  	W weight;
};

template<class L, class W, class N> class Graph {
public:
  	typedef L label;
  	typedef W weight;
  	typedef N node;
  	typedef Edge_<weight, node> Edge;
  	typedef ArrayList<node*> list_of_nodes;
  	typedef typename ArrayList<node*>::position list_of_nodes_pos;
  	typedef ArrayList<Edge> list_of_edges;

    /* methods */
  	virtual bool empty() const = 0;
  	virtual void ins_node(node&) = 0;
  	virtual void ins_edge(node, node, weight) = 0;
  	virtual void delete_node(node) = 0;
  	virtual void delete_edge(node, node) = 0;
  	// virtual bool exists_node(node) = 0;
  	// virtual bool exists_edge(node, node) = 0;
    virtual list_of_nodes adjacent(node) const = 0;
  	virtual list_of_nodes list_nodes() const = 0;
  	virtual label read_label(node) const = 0;
  	virtual void write_label(node, label) = 0;
  	virtual weight read_weight(node, node) const = 0;
  	virtual void write_weight(node, node, weight) = 0;
  	virtual int num_of_nodes() = 0;
  	virtual int num_of_edges() = 0;
};


#endif /* GRAPH_H */
