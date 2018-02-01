#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H
#include "exceptions.h"
#include "../graph.h"

template<class W> class EdgeInfo {
public:
  	W weight;
  	bool empty;
  	EdgeInfo() {
  		  empty = true;
  	}
};

template<class L, class W> class NodeInfo {
public:
  	L label;
  	bool empty;
  	void *info; // points to a generic type
  	EdgeInfo<W> *edges; // array of edges

  	NodeInfo() {
  		  info = 0;
  		  empty = true;
  	}

  	~NodeInfo() {
  		  if (!empty) delete [] edges;
    }
};

/* Graph node */
class GNode {
public:
  	GNode(int i) {
  		  id_node = i;
        used = true;
  	}
  	GNode() { used = false; }
  	int getId() {
        if(used) return id_node;
        else {
            throw InvalidNode();
        }
    }
  	void setId(int id) {
        id_node = id;
        used = true;
    }
    bool getUsed() { return used; }
private:
    int id_node;
    bool used;
};


template<class L, class W> class MatrixGraph : public Graph<L, W, GNode> {
public:
    typedef L label;
    typedef W weight;
    typedef GNode node;
    typedef Edge_<weight, node> Edge;
    typedef Graph<label, weight, node> Graph_;
    typedef typename Graph_::list_of_nodes list_of_nodes;
		typedef typename Graph_::list_of_nodes_pos list_of_nodes_pos;

    MatrixGraph(int);
    ~MatrixGraph();
    bool empty() const;
    void ins_node(GNode &);
    void ins_edge(node, node, weight);
    void delete_node(node);
    void delete_edge(node, node);
		bool exists_node(node) const;
		bool exists_edge(node, node) const;
    list_of_nodes adjacent(node) const;
    list_of_nodes list_nodes() const;
    label read_label(node) const;
    void write_label(node, label);
    weight read_weight(node, node) const;
    void write_weight(node, node, weight);
		int num_of_nodes() {
			  return nodes;
		};
		int num_of_edges() {
			  return edges;
		};

 private:
    NodeInfo<L, W>* matrix;
    int dimension;
    int nodes; // num of nodes
		int edges; // num of edges
};


template<class L, class W>
  	MatrixGraph<L, W>::MatrixGraph(int _dimension) {
  	dimension = _dimension;
  	nodes = 0;
  	edges = 0;
    // it actually isn't a matrix, but a array
  	matrix = new NodeInfo<L, W> [dimension];
  	for (int i = 0; i < dimension; i++) {
        matrix[i].edges = new EdgeInfo<W>[dimension];
    }
}

template<class L, class W>
MatrixGraph<L, W>::~MatrixGraph() {
	  delete [] matrix;
}

template<class L, class W>
bool MatrixGraph<L, W>::empty() const {
	  return (nodes == 0);
}

template<class L, class W>
void MatrixGraph<L, W>::ins_node(node& N) {
	  int n = 0;
	  if(nodes < dimension) {
        // search for a free position in matrix
  		  while(matrix[n].empty == false) {
            n++;
        }
		    nodes++; // num of nodes
		    matrix[n].empty = false;
	      N.setId(n);
    }
}

template<class L, class W>
void MatrixGraph<L, W>::ins_edge(node n1, node n2, W weight) {
	  matrix[n1.getId()].edges[n2.getId()].weight = weight;
   	matrix[n1.getId()].edges[n2.getId()].empty = false;
	  edges++;
}


template<class L, class W>
void MatrixGraph<L, W>::delete_node(node n) {
  	// WARNING: check if there aren't in/out edges to/from the node
  	bool del = true;
  	int i = 0;
    // check if there aren't output edges from n
  	while(i < dimension && del) {
  		  if (!matrix[n.getId()].edges[i].empty) {
  			    del = false;
        }
        i++;
    }
    // check if there aren't input edges from n
    i = 0;
    while(i < dimension && del) {
  		  if(!matrix[i].empty && !matrix[i].edges[n.getId()].empty) {
  			    del = false;
        }
        i++;
    }

  	if(del) {
  		  delete matrix[n.getId()].edges;
  		  matrix[n.getId()].empty = true;
  	}
}

template<class L, class W>
void MatrixGraph<L, W>::delete_edge(node n1, node n2) {
	  matrix[n1.getId()].edges[n2.getId()].empty = true;
	  edges--;
}

template<class L, class W>
bool MatrixGraph<L, W>::exists_node(node n) const {
    if(n.getUsed()) return(!matrix[n.getId()].empty);
    else return false;
}

template<class L, class W>
bool MatrixGraph<L, W>::exists_edge(node n1, node n2) const {
    if(exists_node(n1) && exists_node(n2)) {
        return(!matrix[n1.getId()].edges[n2.getId()].empty);
    }
    else return false;
}

template<class L, class W>
typename MatrixGraph<L, W>::list_of_nodes MatrixGraph<L, W>::adjacent(node n) const {
  	list_of_nodes list(nodes - 1); // worst scenario nodes - 1 adjacencies
  	for(int i = 0; i < dimension; i++) {
  		  if (!matrix[n.getId()].edges[i].empty) {
  			    list.insert(new GNode(i), list.begin());
  		  }
  	}
  	return list;
}

template<class L, class W>
typename MatrixGraph<L, W>::list_of_nodes MatrixGraph<L, W>::list_nodes() const {
  	list_of_nodes list(nodes - 1);
  	for (int i = 0; i < dimension; i++) {
    		if (!matrix[i].empty) {
    			  list.insert(new GNode(i), list.begin());
        }
    }
    return list;
}

template<class L, class W>
L MatrixGraph<L, W>::read_label(node n) const {
	  return matrix[n.getId()].label;
}

template<class L, class W>
void MatrixGraph<L, W>::write_label(node n, L label) {
	  matrix[n.getId()].label = label;
}

template<class L, class W>
W MatrixGraph<L, W>::read_weight(node n1, node n2) const {
	  return matrix[n1.getId()].edges[n2.getId()].weight;
}

template<class L, class W>
void MatrixGraph<L, W>::write_weight(node n1, node n2, W weight) {
    matrix[n1.getId()].edges[n2.getId()].weight = weight;
}

#endif /* MATRIX_GRAPH_H */
