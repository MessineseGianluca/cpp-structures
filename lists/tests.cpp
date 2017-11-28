//============================================================================
// Name        : Lists.cpp
// Author      : Gianluca Messinese
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "array/array_list.h"
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

    std::cin.get();

    return 0;
}
