#include <iostream>
#include <algorithm>
#include "BinarySearchTree.h"

bool isOnlySpace(const std::string& str) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ') {
            return false;
        }
    }
    return true;
}

std::string reverse(const std::string& strSrc) {
    std::string rev(strSrc);
    std::reverse(rev.begin(), rev.end());
    return rev;
}

Node<char>* inAndPre(const std::string& inOrder, std::stringstream& preStream) {
    if (inOrder == "" || isOnlySpace(inOrder)) {
        return nullptr;
    }
    else {
        Node<char>* root = new Node<char>;
        char tempKey;
        preStream >> tempKey;
        root->key = tempKey;

        size_t pos = inOrder.find(tempKey);

        std::string leftStr;
        if (pos == 0) {
            leftStr = "";
        } else {
            leftStr = inOrder.substr(0, pos);
        }
        std::string rightStr = inOrder.substr(pos + 1);

        Node<char>* leftChild = inAndPre(leftStr, preStream);
        root->left = leftChild;
        if (leftChild) {
            leftChild->parent = root;
        }

        Node<char>* rightChild = inAndPre(rightStr, preStream);
        root->right = rightChild;
        if (rightChild) {
            rightChild->parent = root;
        }

        return root;
    }
}

void createFromInAndPre(BST<char>& tree, const std::string& inOrder, const std::string& preOrder) {
    std::stringstream preStream(preOrder);
    tree.root = inAndPre(inOrder, preStream);
}

Node<char>* inAndPost(const std::string& inOrder, std::stringstream& preStream) {
    if (inOrder == "" || isOnlySpace(inOrder)) {
        return nullptr;
    }
    else {
        Node<char>* root = new Node<char>;
        char tempKey;
        preStream >> tempKey;
        root->key = tempKey;

        size_t pos = inOrder.find(tempKey);

        std::string leftStr;
        if (pos == 0) {
            leftStr = "";
        } else {
            leftStr = inOrder.substr(0, pos);
        }
        std::string rightStr = inOrder.substr(pos + 1);

        Node<char>* rightChild = inAndPost(rightStr, preStream);
        root->right = rightChild;
        if (rightChild) {
            rightChild->parent = root;
        }

        Node<char>* leftChild = inAndPost(leftStr, preStream);
        root->left = leftChild;
        if (leftChild) {
            leftChild->parent = root;
        }

        return root;
    }
}

void createFromInAndPost(BST<char>& tree, const std::string& inOrder, const std::string& postOrder) {
    std::string reversed;
    reversed = reverse(postOrder);
    std::stringstream postStream(reversed);
    tree.root = inAndPost(inOrder, postStream);
}
