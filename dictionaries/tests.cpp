#include <iostream>
#include "hash_table/hash_table.h"
#include <string>
int main() {
    HashTable<long, std::string> students(3);
    Pair<long, std::string> stud;
    stud.key = 670756;
    stud.value = "Alex";
    students.insert(stud);
    stud.key = 670700;
    stud.value = "Gianluca";
    students.insert(stud);
    Pair<long, std::string> *temp = students.find(670756);
    if(temp == NULL) {
        std::cout << "NULL Pair";
    } else {
        std::cout << temp->value << std::endl;
    }
    stud.key = 670700;
    stud.value = "Marco";
    students.insert(stud);

    temp = students.find(670700);
    if(temp == NULL) {
        std::cout << "NULL Pair";
    } else {
        std::cout << temp->value << std::endl;
    }
    return 0;
}
