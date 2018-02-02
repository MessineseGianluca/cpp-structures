#include "exceptions.h"

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
