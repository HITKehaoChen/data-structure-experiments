#include <iostream>
#include "list.h"

int main() {
    // Test linked list
    ListLinked<int> myList;
    int temp;
    std::cin >> temp;
    NodeLinked<int>* node = new NodeLinked<int>;
    node->key = temp;
    myList.insert(node);

    NodeLinked<int>* tempNode = myList.search(temp);
    std::cout << tempNode->key << std::endl;
    return 0;
}
