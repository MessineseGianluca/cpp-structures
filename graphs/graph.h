#ifndef GRAPH_H
#define GRAPH_H
#include "../lists/array/array_list.h"
#include "../queues/linked/linked_queue.h"
#include "exceptions.h"
#include "gnode.h"

template<class W, class N> class Edge_ {
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
  	virtual bool exists_node(node) const = 0;
  	virtual bool exists_edge(node, node) const = 0;
    virtual list_of_nodes adjacent(node) const = 0;
  	virtual list_of_nodes list_nodes() const = 0;
  	virtual label read_label(node) const = 0;
  	virtual void write_label(node, label) = 0;
  	virtual weight read_weight(node, node) const = 0;
  	virtual void write_weight(node, node, weight) = 0;
  	virtual int num_of_nodes() const = 0;
  	virtual int num_of_edges() const = 0;
    virtual int dim() const = 0;
    void controller_DFS(node) const; // call it for DFS
    void BFS(node) const;
private:
    void DFS(node, bool *) const;
    // is_connected, Dijkstra
};

template<class L, class W, class N> void Graph<L, W, N>::controller_DFS(node n) const {
    int graph_d = dim();
    bool marks[graph_d];
    for(int i = 0; i < graph_d; i++) marks[i] = false;
    std::cout << std::endl;
    DFS(n, marks);
    std::cout << std::endl;

}

template<class L, class W, class N> void Graph<L, W, N>::DFS(node n, bool *marks) const {
    list_of_nodes_pos p;
    std::cout << read_label(n) << " ";
    marks[n.getId()] = true;
    list_of_nodes ls = adjacent(n);
    p = ls.begin();
    while(!ls.end(p)) {
        GNode c(ls.read(p)->getId());
        if(marks[c.getId()] == false) {
            DFS(c, marks);
        }
        p = ls.next(p);
    }
}

template<class L, class W, class N> void Graph<L, W, N>::BFS(node n) const {
    LinkedQueue<node> q;
    list_of_nodes list;
    list_of_nodes_pos p;
    int graph_d = dim();
    bool marks[graph_d];
    for(int i = 0; i < graph_d; i++){
        marks[i] = false;
    }
    std::cout << std::endl;
    q.queue(n);
    while(!q.empty()) {
        node c = q.read();
        q.dequeue();
        if(!marks[c.getId()])
        std::cout << read_label(c) << " ";
        marks[c.getId()] = true;
        list = adjacent(c);
        p = list.begin();
        while(!list.end(p)) {
            node v(list.read(p)->getId());
            if(!marks[v.getId()]) {
                q.queue(v);
            }
            p = list.next(p);
        }
    }
    std::cout << std::endl;
}

#endif /* GRAPH_H */
