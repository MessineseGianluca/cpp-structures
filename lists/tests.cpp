#include <iostream>
#include "array/array_list.h"
#include "linked/linked_list.h"
#define DIM 10

int main() {
    /****************************** Array Lists ******************************/
    ArrayList<int> my_array_list(DIM);
    for(int i = 0; i < DIM; i++) {
        my_array_list.insert(i, i + 1);
    }
    std::cout << "My list: " << my_array_list << std::endl;

    my_array_list.insert(10, 11);
    my_array_list.insert(3, 5);
	  my_array_list.erase(5);
    std::cout << std::endl << "My updated list: " << my_array_list <<std::endl;

    my_array_list.invert();
    std::cout << std::endl << "My inverted list: " << my_array_list << std::endl;

    char a[DIM] = "anna";
    ArrayList<char> my_array_list2(a, 4);
    std::cout << std::endl << "My list2: " << my_array_list2;
    if(my_array_list2.is_palindrome())
    	std::cout << " is palindrome" << std::endl;


    /****************************** Linked Lists ******************************/
    LinkedList<int> my_link_list;

    my_link_list.insert(4, my_link_list.begin());
    my_link_list.insert(5, my_link_list.begin());
    my_link_list.insert(4, my_link_list.begin());

    LinkedList<int> my_link_list2;
    my_link_list2 = my_link_list;

    std::cout << "my new list is: " << my_link_list2 << std::endl;

    if(my_link_list == my_link_list2) {
        std::cout << my_link_list << " and " << my_link_list2 << " are equal."
        << std::endl;
    }

    my_link_list2.insert(3, my_link_list2.begin());

    if(my_link_list == my_link_list2) {
        std::cout << my_link_list << " and " << my_link_list2 << " are equal."
        << std::endl;
    } else {
        std::cout << my_link_list << " and " << my_link_list2
        << " are not equal." << std::endl;
    }

    my_link_list2.erase(my_link_list2.begin());
    my_link_list2.erase(my_link_list2.begin());
    std::cout << "My updated list is: " << my_link_list2 << std::endl;


    char b[] = "open source";
    LinkedList<char> my_link_list3(b, 11);
    std::cout << "my new list is: " << my_link_list3 << std::endl;

    // exception tests
    LinkedList<char> my_link_list4;
    my_link_list4.insert('a', my_link_list3.begin()); //invalid pos exception
    my_link_list4.insert('b', my_link_list4.begin());
    my_link_list4.erase(my_link_list3.begin()); //invalid pos exception
    std::cout << "my new list is: " << my_link_list4 << std::endl;

    LinkedList<char> my_link_list5;
    my_link_list5.insert('s', my_link_list5.begin());
    my_link_list5.insert('g', my_link_list5.begin());
    my_link_list5.insert('m', my_link_list5.begin());
    my_link_list5.insert('l', my_link_list5.begin());
    my_link_list5.insert('t', my_link_list5.begin());
    my_link_list5.insert('a', my_link_list5.begin());
    my_link_list5.insert('r', my_link_list5.begin());
    my_link_list5.insert('i', my_link_list5.begin());
    std::cout << "my new list is: " << my_link_list5 << std::endl;
    my_link_list5.natural_merge_sort();
    std::cout << "my ordered list is: " << my_link_list5 << std::endl;

    //Lists of Lists(coming soon)
    /*
    LinkedList<char> l1("hello", 5);
    LinkedList<char> l2("world!", 6);
    LinkedList< LinkedList<char> > ll;
    ll.insert(l1, ll.begin());
    ll.insert(l2, ll.begin());
    //std::cout << &ll;
    */

    return 0;
}
