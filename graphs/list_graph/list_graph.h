#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H
#include "../graph.h"
#include "../../lists/linked/linked_list.h"

template<class W> class EdgeInfo {
public:
    W weight;
    GNode _to; // info of the input node the edge refers to
};

template<class L, class W>
class NodeInfo {
public:
    L label;
    bool empty;
    void* info;
    LinkedList< EdgeInfo< W > > edges;
    NodeInfo() {
        info = 0;
        empty = true;
    }
};

template<class L, class W>
class ListGraph : public Graph<L, W, GNode> {
public:
    typedef L label;
    typedef W weight;
    typedef GNode node;
    typedef Edge_<weight, node> Edge;
    typedef Graph<label, weight, node> Graph_;
    typedef typename Graph_::list_of_nodes list_of_nodes;
    typedef typename Graph_::list_of_nodes_pos list_of_nodes_pos;

    ListGraph(int);
    ~ListGraph();

    bool empty() const;
    void ins_node(GNode&);
    void ins_edge(node, node, weight);
    void delete_node(node);
    void delete_edge(node, node);
    bool exists_node(node) const;
    bool exists_edge(node, node) const;
    list_of_nodes adjacent(node) const ;
    list_of_nodes list_nodes() const ;
    label read_label(node) const ;
    void write_label(node, label) ;
    weight read_weight(node, node) const ;
    void write_weight(node, node, weight) ;
    int num_of_nodes() const {
        return nodes;
    }
    int num_of_edges() const {
        return edges;
    }
    int dim() const {
        return dimension;
    }
private:
    NodeInfo<L, W>* matrix;
    int dimension;
    int nodes; // num of nodes
    int edges; // num of edges
};


template<class L, class W>
    ListGraph<L, W>::ListGraph(int _dimension) {
    dimension = _dimension;
    nodes = 0;
    edges = 0;
    matrix = new NodeInfo<L, W>[dimension];
    for (int i = 0; i < dimension; i++)
        matrix[i].edges.create();
}

template<class L, class W>
ListGraph<L, W>::~ListGraph() {
    delete [] matrix;
}

template<class L, class W>
bool ListGraph<L, W>::empty() const {
    return (nodes == 0);
}

template<class L, class W>
void ListGraph<L, W>::ins_node(node& N) {
    int j = 0;
    // search for a free position in matrix
    if (nodes < dimension) {
        while (matrix[j].empty == false) {
            j++;
        }
        nodes++;
        matrix[j].empty = false;
    }
    N.setId(j);
}

template<class L, class W>
void ListGraph<L, W>::ins_edge(node n1, node n2, W weight) {
    EdgeInfo< W > I;
    if(!exists_node(n1) || !exists_node(n2)) {
        throw InvalidNode();
    } else if(exists_edge(n1, n2)) {
        throw EdgeAlreadyExists();
    } else {
        I.weight = weight;
        I._to = n2;
        // insert I inside the list of edges
        matrix[n1.getId()].edges.insert(I, matrix[n1.getId()].edges.begin());
        edges++;
    }
}


template<class L, class W>
void ListGraph<L, W>::delete_node(node n) {
    bool del = true;
    typename LinkedList< EdgeInfo< W > >::position p;
    int i = 0;
    node temp;
    if(exists_node(n)) {
        // check for ouput edges from n
        if (!matrix[n.getId()].edges.empty()) {
            del = false;
        }
        // check for input edges to n
        while(i < dimension && del) {
            if(!matrix[i].edges.empty()) {
                p = matrix[i].edges.begin();
                while(!matrix[i].edges.end(p) && del) {
                    temp = matrix[i].edges.read(p)._to;
                    if(n.getId() == temp.getId()) {
                        del = false;
                    } else {
                        p = matrix[i].edges.next(p);
                    }
                }
            }
            i++;
        }
        if(del) {
            matrix[n.getId()].empty = true;
        }
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
void ListGraph<L, W>::delete_edge(node n1, node n2) {
    if(exists_node(n1) && exists_node(n2)) {
      	typename LinkedList< EdgeInfo< W > >::position p;
      	p = matrix[n1.getId()].edges.begin();
      	bool found = false;
      	while(!matrix[n1.getId()].edges.end(p) && !found){
            if (matrix[n1.getId()].edges.read(p)._to.getId() == n2.getId())
                found = true;
            else
                p = matrix[n1.getId()].edges.next(p);
      	}
      	if (found) matrix[n1.getId()].edges.erase(p);
        edges--;
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
bool ListGraph<L, W>::exists_node(node n) const {
    if(n.getUsed()) return(!matrix[n.getId()].empty);
    else return false;
}

template<class L, class W>
bool ListGraph<L, W>::exists_edge(node n1, node n2) const {
  	typename LinkedList< EdgeInfo< W > >::position p;
    bool found = false;
    if(exists_node(n1) && exists_node(n2)) {
        if(!matrix[n1.getId()].edges.empty()) {
            p = matrix[n1.getId()].edges.begin();
            while(!matrix[n1.getId()].edges.end(p) && !found) {
                if(matrix[n1.getId()].edges.read(p)._to.getId() == n2.getId()) {
                    found = true;
                } else {
                    p = matrix[n1.getId()].edges.next(p);
                }
            }
        }
        return found;
    }
    else return false;
}

template<class L, class W>
typename ListGraph<L, W>::list_of_nodes ListGraph<L, W>::adjacent(node n) const{
    list_of_nodes list(nodes - 1);
    int i;
    typename LinkedList< EdgeInfo< W > >::position p;
    if(exists_node(n)) {
        if(!matrix[n.getId()].edges.empty()) {
            p = matrix[n.getId()].edges.begin();
            while(!matrix[n.getId()].edges.end(p)) {
                i = matrix[n.getId()].edges.read(p)._to.getId();
                list.insert(new GNode(i), list.begin());
                p = matrix[n.getId()].edges.next(p);
            }
        }
        return list;
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
typename ListGraph<L, W>::list_of_nodes ListGraph<L, W>::list_nodes() const {
    list_of_nodes list(nodes);  // worst scenario nodes - 1 adjacencies
    for (int i = 0; i < dimension; i++) {
        if (!matrix[i].empty)
            list.insert(new GNode(i), list.begin());
    }
    return list;
}

template<class L, class W>
L ListGraph<L, W>::read_label(node n) const {
    if(exists_node(n)) {
        return matrix[n.getId()].label;
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
void ListGraph<L, W>::write_label(node n, L label) {
    if(exists_node(n)) {
        matrix[n.getId()].label = label;
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
W ListGraph<L, W>::read_weight(node n1, node n2) const {
  	typename LinkedList< EdgeInfo< W > >::position p;
    if(exists_node(n1) && exists_node(n2)) {
        // check if the edge exists
      	p = matrix[n1.getId()].edges.begin();
      	bool found = false;
      	while(!matrix[n1.getId()].edges.end(p) && !found) {
      		  if(matrix[n1.getId()].edges.read(p)._to.getId() == n2.getId())
      			    found = true;
      		  else
      				  p = matrix[n1.getId()].edges.next(p);
      	}
      	if(found) {
      		  return matrix[n1.getId()].edges.read(p).weight;
        }
    } else {
        throw InvalidNode();
    }
}

template<class L, class W>
void ListGraph<L, W>::write_weight(node n1, node n2, W weight) {
  	typename LinkedList< EdgeInfo< W > >::position p;
    if(exists_node(n1) && exists_node(n2)) {
        // check if the edge exists
      	p = matrix[n1.getId()].edges.begin();
      	bool found = false;
      	while(!matrix[n1.getId()].edges.end(p) && !found) {
            if(matrix[n1.getId()].edges.read(p)._to.getId() == n2.getId())
                found = true;
        	else
                p = matrix[n1.getId()].edges.next(p);
      	}
      	if(found) {
            EdgeInfo< W > I;
            I.weight = weight;
            I._to = n2;
            matrix[n1.getId()].edges.write(I, p);
      	}
    } else {
        throw InvalidNode();
    }
}



#endif /* LIST_GRAPH_H */
