#include "heap/heap_pq.h"
#include <iostream>

int main() {
    Heap_Priority_Queue<int> C;
    C.insert(1);
    C.insert(12);
    C.insert(19);
    C.insert(7);
    C.delete_min();
    C.insert(0);
    std::cout << C.min() << std::endl;
    C.insert(11);
    C.delete_min();
    std::cout << C.min() << std::endl;
    C.insert(5);
    std::cout << C.min() << std::endl;
    C.insert(21);
    C.insert(18);
    C.delete_min();
    std::cout << C.min() << std::endl;
    C.insert(3);
    std::cout << C.min() << std::endl;
    C.delete_min();
    std::cout << C.min() << std::endl;

    return 0;
}
