#include "matrix_graph/matrix_graph.h"
#include <string>

int main() {
  	MatrixGraph<std::string, double> G(10);
  	GNode n1, n2, n3, n4, n5, n6;

  	G.ins_node(n1);
  	G.write_label(n1, "a");
  	G.ins_node(n2);
  	G.write_label(n2, "b");
  	G.ins_node(n3);
  	G.write_label(n3, "c");
  	G.ins_node(n4);
  	G.write_label(n4, "d");
  	G.ins_node(n5);
  	G.write_label(n5, "e");
  	G.ins_node(n6);
  	G.write_label(n6, "f");

  	G.ins_edge(n1, n2, 1.0);
  	G.ins_edge(n1, n3, 0.9);
  	G.ins_edge(n1, n5, 0.3);
  	G.ins_edge(n2, n4, 0.1);
  	G.ins_edge(n2, n6, 0.2);
  	G.ins_edge(n3, n4, 1.0);
  	G.ins_edge(n3, n6, 0.7);
  	G.ins_edge(n4, n1, 0.5);
  	G.ins_edge(n5, n2, 0.4);
  	G.ins_edge(n5, n3, 0.2);
  	G.ins_edge(n6, n4, 0.1);

  	std::cout << "\nNum of nodes: " << G.num_of_nodes();
  	std::cout << "\nNum of edges: " << G.num_of_edges();
    // Warning! n6 isn't deleted because there are in/out edges to/from him
  	G.delete_node(n6);
  	std::cout << "\nNum of nedes: " << G.num_of_nodes() << std::endl;

  	MatrixGraph<std::string, double>::list_of_nodes L = G.adjacent(n1);
  	MatrixGraph<std::string, double>::list_of_nodes_pos p;

  	std::cout << "Adjacent of:  " << G.read_label(n1) << "--> ";
  	p = L.begin();
  	while (!L.end(p)) {
  		  std::cout <<  G.read_label(*(L.read(p))) << " ";
  		  p = L.next(p);
  	}

    GNode n7;
    if(G.exists_node(n7)) {
        std::cout << "The node exists";
    } else {
      std::cout << "The node doesn't exists";
    }
}
