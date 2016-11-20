#include <iostream>
#include <sstream>
#include "BinarySearchTree.h"

int main() {
    std::string inOrder{"D B E A F C"};
    std::string preOrder{"A B D E C F"};
    std::string postOrder{"D E B F C A"};

    std::cout << "This is a tree in three kinds of traversal:" << std::endl;
    std::cout << "In-Order: " << inOrder << std::endl
              << "Pre-Order:" << preOrder << std::endl
              << "Post-Order:" << postOrder << std::endl << std::endl;

    /* Construct Tree from given In-Order and Pre-Order Traversals */
    std::cout << "This tree is created by In-Order and Pre-Order traversals"
              << std::endl
              << '\t';

    BST<char> treeCreatedFromInAndPre;
    createFromInAndPre(treeCreatedFromInAndPre, inOrder, preOrder);
    treeCreatedFromInAndPre.preOrderWalk();
    std::cout << std::endl;

    /* Construct Tree from given In-Order and Post-Order Traversals */
    std::cout << "This tree is created by In-Order and Post-Order traversals"
              << std::endl
              << '\t';

    BST<char> treeCreatedFromInAndPost;
    createFromInAndPost(treeCreatedFromInAndPost, inOrder, postOrder);
    treeCreatedFromInAndPost.preOrderWalk();
    std::cout << std::endl;

    /* Explanation on Why Pre-Order and Post-Order Traversals Fail to Construct a Tree */
    std::cout << "However, with Pre-Order and Post-Order traversals, we cannot construct a tree."
              << std::endl
              << "It's because with only these two traversals, we can only get to know which one"
              << std::endl
              << "is the 'root' node, having no idea that which part is representative of a left"
              << std::endl
              << "subtree or a right subtree. While with In-Order traversal taken into considera-"
              << std::endl
              << "tion, the left part before the 'root' node is the left tree, the same to right."
              << std::endl
              << "In conclusion, there is no construction made from given In-Order and Pre-Order"
              << std::endl
              << "traversals."
              << std::endl;

    /*Post Script:
     *
     *  The tree data type in the program is binary search tree in fact.
     *
     */

    return 0;
}
