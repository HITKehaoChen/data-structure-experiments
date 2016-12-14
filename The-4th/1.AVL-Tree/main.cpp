#include <iostream>
#include <sstream>
#include <fstream>
#include "binary_tree.h"

template<typename T>
std::istream& operator>>(std::istream& input, AVLTree<T>& tree);

int main() {

    // Insertion
    AVLTree<int> avlTestInsertion;
    avlTestInsertion.insert(5);
    avlTestInsertion.insert(4);
    std::cout << "There is a BST:" << std::endl;
    std::cout << "   5   " << std::endl;
    std::cout << "  /" << std::endl;
    std::cout << " 2" << std::endl;
    std::cout << "Now let's insert a node whose key is 2 in a normal BST insert:"
              << std::endl;
    avlTestInsertion.insert(2);
    std::cout << "   5" << std::endl;
    std::cout << "  /" << std::endl;
    std::cout << " 2" << std::endl;
    std::cout << "  \\" << std::endl;
    std::cout << "   4" << std::endl;
    std::cout << "After the self-balancing of AVL tree, we get (in level order traversal):"
              << std::endl;
    avlTestInsertion.levelPrint();
    std::cout << "And the sequence of nodes is:" << std::endl;
    avlTestInsertion.inOrderWalk();
    std::cout << std::string(60, '*') << std::endl;

    // Deletion
    AVLTree<int> avlTestDeletion;
    avlTestDeletion.insert(5);
    avlTestDeletion.insert(2);
    avlTestDeletion.insert(7);
    avlTestDeletion.insert(4);
    std::cout << "Consider another BST:" << std::endl;
    std::cout << "   5   " << std::endl;
    std::cout << "  / \\" << std::endl;
    std::cout << " 2   7" << std::endl;
    std::cout << "  \\" << std::endl;
    std::cout << "   4" << std::endl;
    std::cout << "Now let's delete the node whose key is 7 in a normal BST deletion:"
              << std::endl;
    avlTestDeletion.remove(avlTestDeletion.search(7));
    std::cout << "   5" << std::endl;
    std::cout << "  /" << std::endl;
    std::cout << " 2" << std::endl;
    std::cout << "  \\" << std::endl;
    std::cout << "   4" << std::endl;
    std::cout << "After the self-balancing of AVL tree, we get (in level order traversal):"
              << std::endl;
    avlTestDeletion.levelPrint();
    std::cout << "And the sequence of nodes is:" << std::endl;
    avlTestInsertion.inOrderWalk();
    std::cout << std::string(60, '*') << std::endl;

    // Read from file
    std::ifstream inputFromFile("LL.txt", std::ios_base::in);
    AVLTree<int> avlTestFile;
    inputFromFile >> avlTestFile;
    std::cout << "Here is the AVL tree read from file after one of four kinds of rotation"
              << std::endl;
    avlTestFile.levelPrint();
    std::cout << "Here is the explanation:" << std::endl;
    std::string explanationLine = "";
    while (getline(inputFromFile, explanationLine)) {
        std::cout << explanationLine << std::endl;
    }
    return 0;
}

template<typename T>
std::istream& operator>>(std::istream& input, AVLTree<T>& tree) {
    std::string inputString;
    std::getline(input, inputString);
    std::stringstream sStream(inputString);
    char key;
    while (sStream >> key) {
        tree.insert(static_cast<int>(key - '0'));
    }
    return input;
}
