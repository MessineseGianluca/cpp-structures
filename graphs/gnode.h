/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */
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
     // the assignment operator
    GNode &operator = (GNode g) {
        setId(g.getId());
        return *this;
    }
private:
    int id_node;
    bool used;
};
