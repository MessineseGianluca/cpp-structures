#include <iostream>
#include "array/array_list.h"
#include "linked/linked_list.h"
#define DIM 10

int main() {
    ArrayList<int> my_list(DIM);
    for(int i = 0; i < DIM; i++) {
        my_list.insert(i, i + 1);
    }
    std::cout << "My list:" << std::endl;
    for(int i = 1; i <= my_list.size(); i++)
    	std::cout << my_list.read(i) << std::endl;

    std::cout << std::endl << "My updated list:" << std::endl;
    my_list.insert(10, 11);
    my_list.insert(3, 5);
	my_list.erase(5);

	for(int i = 1; i <= my_list.size(); i++)
    	std::cout << my_list.read(i) << std::endl;



	std::cout << std::endl << "My inverted list:" << std::endl;
    my_list.invert();
    for(int i = 1; i <= my_list.size(); i++)
        std::cout << my_list.read(i) << std::endl;



    char a[DIM] = {'a', 'n', 'n', 'a'};
    std::cout << std::endl << "My list2:" << std::endl;
    ArrayList<char> my_list2(a, 4);
    for(int i = 1; i <= my_list2.size(); i++)
        std::cout << my_list2.read(i);

    if(my_list2.is_palindrome())
    	std::cout << " is palindrome" << std::endl;


    LinkedList<int> my_link_list;

    my_link_list.insert(4, my_link_list.begin());
    my_link_list.insert(5, my_link_list.begin());
    my_link_list.insert(4, my_link_list.begin());

    LinkedList<int> my_link_list2;
    my_link_list2 = my_link_list;

    std::cout << "my list is: " << my_link_list2;

    if(my_link_list == my_link_list2) std::cout << "they are equal" << std::endl;
    return 0;
}
