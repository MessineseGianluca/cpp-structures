#ifndef GRAPH_H
#define GRAPH_H
#include "../lists/array/array_list.h"
#include "../queues/linked/linked_queue.h"
//#include "../stacks/linked/linked_stack.h"
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
    /*struct Info {
        int *marks;
        W path_weight;
        LinkedStack<node> path;
    };*/

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
    bool controller_is_connected(node n) const; //call it to know if thegraph is connected
    //bool is_in_adj(list_of_nodes, node) const;
    //void controller_path_more_than(node source, W k) const;
private:
    void DFS(node, bool *) const;
    //bool path_more_than(node source, node e, W k, Info &) const;
    void is_connected(int &, bool *, node , int) const;
};

template<class L, class W, class N>
bool Graph<L, W, N>::controller_is_connected(node n) const {
    int count = 0;
    int graph_d = dim();
    int num = num_of_nodes();
    bool marks[graph_d];
    for(int i = 0; i < graph_d; i++) {
        marks[i] = false;
    }
    is_connected(count, marks, n, num);
    if(count == num) {
        return true;
    } else {
        return false;
    }
}

template<class L, class W, class N>
void Graph<L, W, N>::is_connected(int &count, bool *marks, node n, int num) const {
    if(!marks[n.getId()]) {
        count++;
        marks[n.getId()] = true;
    }
    list_of_nodes temp = adjacent(n);
    list_of_nodes_pos p = temp.begin();
    while(!temp.end(p) && count != num) {
        node c(temp.read(p)->getId());
        if(!marks[c.getId()]) {
            is_connected(count, marks, c, num);
        }
        p = temp.next(p);
    }
}

template<class L, class W, class N> void Graph<L, W, N>::controller_DFS(node n) const {
    if(controller_is_connected(n)) {
        int graph_d = dim();
        bool marks[graph_d];
        for(int i = 0; i < graph_d; i++) marks[i] = false;
        std::cout << std::endl;
        DFS(n, marks);
        std::cout << std::endl;
    } else {
        throw GraphIsNotConnected();
    }
}

template<class L, class W, class N> void Graph<L, W, N>::DFS(node n, bool *marks) const {
    list_of_nodes_pos p;
    std::cout << read_label(n) << " ";
    marks[n.getId()] = true;
    list_of_nodes ls = adjacent(n);
    p = ls.begin();
    while(!ls.end(p)) {
        node c(ls.read(p)->getId());
        if(marks[c.getId()] == false) {
            DFS(c, marks);
        }
        p = ls.next(p);
    }
}

template<class L, class W, class N> void Graph<L, W, N>::BFS(node n) const {
    if(controller_is_connected(n)) {
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
    } else {
        throw GraphIsNotConnected();
    }
}
/*
template<class L, class W, class N>
void Graph<L, W, N>::controller_path_more_than(node source, W k) const {
    int num = num_of_nodes();
    list_of_nodes path(num);
    list_of_nodes adj(adjacent(source));
    list_of_nodes_pos p = adj.begin();
    list_of_nodes_pos p_path;
    W path_weight = 0;
    bool found = false;
    if(!adj.empty()) {
        while(!adj.end(p) && !found) {
            node end(adj.read(p)->getId());
            found = path_more_than(source, end, k, path_weight, path);
            p = adj.next(p);
        }
        if(found) {
            std::cout << "The path is: ";
            p_path = path.begin();
            while(!path.end(p_path)) {
                std::cout << read_label(path.read(p_path)->getId());
                p_path = path.next(p_path);
            }
            std::cout << std::endl;
        }
    }
}

template<class L, class W, class N>
bool Graph<L, W, N>::path_more_than(node source, node e, W k, W &path_weight, list_of_nodes &path) const {
    bool found = false;
    int num = num_of_nodes();
    list_of_nodes adj(adjacent(e));
    list_of_nodes_pos p = adj.begin();
    list_of_nodes_pos p_path;
    path.insert_last(new GNode(e.getId()));
    path_weight += read_weight(source, e);
    std::cout << "reading the node: " << read_label(e) << std::endl;
    // std::cout << path << " " << path_weight << std::endl;
    if(adj.size() == 1 && adj.read(p)->getId() == source.getId()) {
        std::cout << "condition 1" << std::endl;
        path_weight = 0;
        p_path = path.begin();
        while(!path.end(p_path)) {
            path.erase(p_path);
        }
        return false;
    }
    if(!is_in_adj(adj, source) && path_weight > k) {
        std::cout << "condition 2" << std::endl;
        return true;
    } else {
        std::cout << "condition 3" << std::endl;
        while(!adj.end(p) && !found) {
            node end(adj.read(p)->getId());
            if(end.getId() != source.getId()) {
                std::cout << "condition 4" << std::endl;
                found = path_more_than(source, end, k, path_weight, path);
            }
            p = adj.next(p);
        }
    }
    return found;
}*/
/*
template<class L, class W, class N>
bool Graph<L, W, N>::is_in_adj(list_of_nodes adj, node n) const {
    bool found = false;
    list_of_nodes_pos p = adj.begin();
    while(!adj.end(p) && !found) {
      if(n.getId() == adj.read(p)->getId()) {
        found = true;
      }
      p = adj.next(p);
    }
    return found;
}

template<class L, class W, class N>
void Graph<L, W, N>::controller_path_more_than(node source, W k) const {
    int graph_d = dim();
    int m[graph_d];
    Info info;
    info.marks = m;
    info.path_weight = 0;
    for(int i = 0; i < graph_d; i++){
        info.marks[i] = 0;
    }
    info.marks[source.getId()] = 1;
    list_of_nodes adj(adjacent(source));
    list_of_nodes_pos p = adj.begin();
    bool found = false;
    if(!adj.empty()) {
        while(!adj.end(p) && !found) {
            node end(adj.read(p)->getId());
            found = path_more_than(source, end, k, info);
            p = adj.next(p);
        }
        if(found) {
            std::cout << "The path is: ";
            while(!info.path.empty()) {
                std::cout << read_label(info.path.read().getId());
                info.path.pop();
            }
        }
    }
}

template<class L, class W, class N>
bool Graph<L, W, N>::path_more_than(node source, node e, W k, Info &info) const {
    bool found;
    list_of_nodes adj = adjacent(e);
    list_of_nodes_pos p = adj.begin();
    info.path.push(e);
    info.path_weight += read_weight(source, e);
    info.marks[e.getId()] = 1;
    if(adj.size() == 1 && (adj.read(p)->getId() == source.getId() || info.marks[e.getId()] == -1)) {
        info.marks[e.getId()] == -1; // black list
        info.path_weight -= read_weight(source, e);
        info.path.pop();
        return false;
    } else if(!adj.empty() && (info.path_weight < k || (is_in_adj(adj, source) && info.path_weight > k))) {
        found = false;
        while(!adj.end(p) && !found) {
            node e(adj.read(p)->getId());
            // check if the node e is marked or is in black list or if is the source
            if(e.getId() != source.getId() && (info.marks[e.getId()] != -1 || info.marks[e.getId()] == 1)) {
                found = path_more_than(source, e, k, info);
            }
            p = adj.next(p);
        }
        // check if the last node of the path has no adjacencies with a
        if(is_in_adj(adjacent(info.path.read()), source)) {
            found = false;
        }
        return found;
    } else if(!adj.empty() && info.path_weight > k) {
        return true;
    } else if(adj.empty() && info.path_weight > k) {
        return true; // end: a path has been found!
    } else {
        info.path.pop();
        info.marks[e.getId()] = 0;
        info.path_weight -= read_weight(source, e);
        return false;
    }
}
*/


#endif /* GRAPH_H */
