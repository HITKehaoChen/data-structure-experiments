#include <iostream>
#include <sstream>
#include "binary_tree.h"

int main() {

    /* Creation */

    // Creation with hash tokens
    BinaryTree<char> treeWithHash;
    std::cout << "Please input a tree in pre-order (WITH '#'):" << std::endl;
    std::cout << '\t';
    std::string stringWithHash;
    std::getline(std::cin, stringWithHash);
    treeWithHash.createWithHash(stringWithHash);
    std::cout << "The tree created with '#' in pre-order is:" << std::endl;
    std::cout << '\t';
    treeWithHash.preOrderWalkR();
    std::cout << std::endl;

    // Creation without hash tokens
    BinaryTree<char> treeNoHash;
    std::cout << "Please input a tree in pre-order (WITHOUT '#'):" << std::endl;
    std::cout << '\t';
    std::cin.ignore();
    std::string stringNoHash("ABDHIECFJG");
    std::getline(std::cin, stringNoHash);
    treeNoHash.createWithoutHash(stringNoHash);
    std::cout << "The tree created without '#' in pre-order is (WITH RECURSION):" << std::endl;
    std::cout << '\t';
    treeNoHash.preOrderWalkR();
    std::cout << std::endl;


    /* Traversal */
    std::cout << "The tree created without '#' in in-order is (WITH RECURSION):" << std::endl;
    std::cout << '\t';
    treeNoHash.inOrderWalkR();
    std::cout << std::endl;
    std::cout << "The tree created without '#' in post-order is (WITH RECURSION):" << std::endl;
    std::cout << '\t';
    treeNoHash.postOrderWalkR();
    std::cout << std::endl;
    std::cout << "The tree created without '#' in pre-order is: (WITHOUT RECURSION)" << std::endl;
    std::cout << '\t';
    treeNoHash.preOrderWalk();
    std::cout << std::endl;
    std::cout << "The tree created without '#' in in-order is: (WITHOUT RECURSION)" << std::endl;
    std::cout << '\t';
    treeNoHash.inOrderWalk();
    std::cout << std::endl;
    std::cout << "The tree created without '#' in post-order is: (WITHOUT RECURSION)" << std::endl;
    std::cout << '\t';
    treeNoHash.postOrderWalk();
    std::cout << std::endl <<  std::string(60, '-') << std::endl << std::endl;


    /* Threaded Tree */
    treeNoHash.getThreaded();
    std::cout << "A threaded tree in pre-order is:" << std::endl;
    std::cout << '\t';
    treeNoHash.threadPreOrderWalk();
    std::cout << "A threaded tree in in-order is:" << std::endl;
    std::cout << '\t';
    treeNoHash.threadedInOrderWalk();
    std::cout << "A threaded tree in post-order is:" << std::endl;
    std::cout << '\t';
    treeNoHash.threadedPostOrderWalk();

    return 0;
}
