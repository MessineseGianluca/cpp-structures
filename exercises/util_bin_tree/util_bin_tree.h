/*
 * Author: Gianluca Messinese, Italy
 * Description: This is teaching material for my university course. Feel free
 * to use/copy/modify this code.
 * Source: For more open source projects visit my github profile:
 * https://github.com/MessineseGianluca
 *
 */

#include "../../trees/tree_list/tree_list.h"

template<class I>
class UtilNTree {
public:
    typedef typename TreeList<I>::node node;
    UtilNTree() {};
    ~UtilNTree() {};
    /* returns the number of leaves in the tree*/
    int n_leaf(const TreeList<I> &T) const;
    /* return the number of nodes in the level k ofthe tree */
    int n_level(const TreeList<I> &T, int k) const;
private:
    void count_leaves(node, const TreeList<I> &, int &) const;
};

template<class I>
int UtilNTree<I>::n_leaf(const TreeList<I> &T) const {
    int count = 0;
    count_leaves(T.root(), T, count);
    return count;
}

template<class I>
void UtilNTree<I>::count_leaves(node n, const TreeList<I> &T, int &counter) const {
    node c;
    if(T.leaf(n)) {
        counter++;
    } else {
        c = T.first_child(n);
        while(!T.last_sibling(c)) {
            count_leaves(c, T, counter);
            c = T.next_sibling(c);
        }
        count_leaves(c, T, counter);
    }
}

template<class I>
int UtilNTree<I>::n_level(const TreeList<I> &T, int k) const {
    int level = 0;
    node n = T.root();
    node c, temp;
    int d = T.depth(n);
    int nodes_counter = 0;
    bool level_reached = false;
    int nodes_in_the_level[d + 1];
    for(int i = 0; i < d + 1; i++) {
        nodes_in_the_level[i] = 0;
    }
    nodes_in_the_level[0] = 1;
    LinkedQueue<node> q;
    if(k <= d && !T.empty()) {
        if(k == 0) {
            nodes_counter = 1;
        } else {
            q.queue(n);
            while(!q.empty() && !level_reached) {
                c = q.read();
                temp = c;
                q.dequeue();
                if(!T.leaf(c)) {
                    level++;
                    c = T.first_child(c);
                    while(!T.last_sibling(c)) {
                        q.queue(c);
                        nodes_in_the_level[level]++;
                        if(level == k) {
                            nodes_counter++;
                        }
                        c = T.next_sibling(c);
                    }
                    // last child node
                    if(level == k) {
                        nodes_counter++;
                    }
                    nodes_in_the_level[level]++;
                    q.queue(c);
                    if(!T.last_sibling(temp)) {
                        level--;
                    }
                }
                nodes_in_the_level[level]--;
                // level needs to be incremented when is reached the last node of a level
                if(nodes_in_the_level[level] == 0) {
                    level++;
                    if(level == k) {
                        level_reached = true;
                    }
                }

            }
        }
    }
    return nodes_counter;
}
