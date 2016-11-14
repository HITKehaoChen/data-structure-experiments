#include <iostream>
#include <sstream>
#include "binary_tree.h"

int main() {
//    std::string inputString;
//    std::getline(std::cin, inputString);
//    std::stringstream sStream(inputString);
//    BinarySearchTree<char> test;
//    if (test.getRoot() == nullptr) {
//        char key;
//        sStream >> key;
//        Node* temp = new Node;
//        temp->left = nullptr;
//        temp->right = nullptr;
//        test.insert(temp);
//    }


    /* Test for walk */
    BinaryTree<char> t;
    for (size_t i = 0; i < 10; ++i) {
        char temp;
        std::cin >> temp;
        t.insert(temp);
    }
    t.postOrderWalk();
    t.preOrderWalk();
    t.levelWalk();
    return 0;
}
