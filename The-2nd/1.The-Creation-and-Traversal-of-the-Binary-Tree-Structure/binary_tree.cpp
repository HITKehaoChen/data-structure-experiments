#include <sstream>
#include "binary_tree.h"

/* Plain BT */

void BinaryTree::createByString(std::string string, size_t index) {
/*    if (string[index] == '#') {

    } else {

    }*/
}

/* BST */

void BinaryTree::insert(Node* x) {
    Node* temp = nullptr;
    Node* walker = root;
    while (walker != nullptr) {
        temp = walker;
        if (x->key < walker->key) {
            walker = walker->left;
        } else {        // the right child is non-decreasing
            walker = walker->right;
        }
    }
    x->parent = temp;
    if (temp == nullptr) {
        root = x;
    } else if (x->key < temp->key) {
        temp->left = x;
    } else {
        temp->right = x;
    }
}

void BinaryTree::insertImproved(Node* x) {
    Node* walker = root;
    if (walker == nullptr) {
        root = x;
        return;
    }
    while (walker != nullptr) {
        if (x->key < walker->key) {
            if (walker->left == nullptr) {
                walker->left = x;
                x->parent = walker;
                return;
            }
            walker = walker->left;
        } else {        // the right child is non-decreasing
            if (walker->right == nullptr) {
                walker->right = x;
                x->parent = walker;
                return;
            }
            walker = walker->right;
        }
    }
}

std::istream& operator>>(std::istream& input, BinaryTree& bst) {
    std::string inputString;
    std::getline(input, inputString);
    std::stringstream sStream(inputString);
    char key;
    while (sStream >> key) {
        Node* temp = new Node;
        temp->key = key;
        bst.insert(temp);
    }
    return input;
}

void in_orderWalk(Node* x) {
    if (x != nullptr) {
        in_orderWalk(x->left);
        std::cout << x->key << ' ' << std::endl;
        in_orderWalk(x->right);
    }
}
