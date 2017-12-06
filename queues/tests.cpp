#include <iostream>
#include "linked/linked_queue.h"

int main() {
    LinkedQueue<char> link_queue;
    link_queue.queue('a');
    link_queue.dequeue();
    link_queue.queue('b');
    link_queue.queue('c');
    link_queue.dequeue();
    link_queue.dequeue();
    link_queue.queue('a');
    std::cout << link_queue.read() << std::endl;
    link_queue.edit('d');
    std::cout << link_queue.read() << std::endl;
    
    return 0;
}
