#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "queue.h"

/*
 * Things that need to be done:
 *      1. create a derived class of Node class.
 *      2. add inheritance
 */


/* Node classes */

template<typename T>
struct Node {
    T key = 0;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
};

/* Tree classes */

template<typename T>
class BST {
private:
    Node<T>* root = nullptr;

    void inOrder(Node<T>* p) const {
        if (p != nullptr) {
            inOrder(p->left);
            std::cout << p->key << ' ';
            inOrder(p->right);
        }
    }

    void preOrder(Node<T>* p) const {
        if (p != nullptr) {
            std::cout << p->key << ' ';
            preOrder(p->left);
            preOrder(p->right);
        }
    }

    void postOrder(Node<T>* p) const {
        if (p != nullptr) {
            postOrder(p->left);
            postOrder(p->right);
            std::cout << p->key << ' ';
        }
    }

    void destroy(Node<T>* p) {
        if (p == nullptr) {
            return;
        } else {
            if (p->left != nullptr) {
                destroy(p->left);
            }
            if (p->right != nullptr) {
                destroy(p->right);
            }
            delete p;
        }
    }


public:
    BST() : root{nullptr} {}

    BST(std::string str) { createByString(str); }

    ~BST() {
        destroy(root);
    }

    void inOrderWalk() const {
        if (root != nullptr) {
            inOrder(root->left);
            std::cout << root->key << ' ';
            inOrder(root->right);
        }
        std::cout << std::endl;
    }

    void preOrderWalk() const {
        if (root != nullptr) {
            std::cout << root->key << ' ';
            preOrder(root->left);
            preOrder(root->right);
        }
        std::cout << std::endl;
    }

    void postOrderWalk() const {
        if (root != nullptr) {
            postOrder(root->left);
            postOrder(root->right);
            std::cout << root->key << ' ';
        }
        std::cout << std::endl;
    }

    void levelWalk() const {
        adtQueue<Node<T>*> queue;
        queue.enQueue(root);
        while (!queue.isEmpty()) {
            Node<T>* temp = queue.deQueue();
            if (temp->left != nullptr) {
                queue.enQueue(temp->left);
            }
            if (temp->right != nullptr) {
                queue.enQueue(temp->right);
            }
            std::cout << temp->key << ' ';
        }
        std::cout << std::endl;
    }

    void insert(T key) {
        Node<T>* p = new Node<T>;
        p->key = key;
        Node<T>* predecessor = nullptr;
        Node<T>* walker = root;
        while (walker != nullptr) {
            predecessor = walker;
            if (p->key < walker->key) {
                walker = walker->left;
            } else {        // The right child is non-decreasing
                walker = walker->right;
            }
        }
        p->parent = predecessor;
        if (predecessor == nullptr) {
            root = p;
        } else if (p->key < predecessor->key) {
            predecessor->left = p;
        } else {
            predecessor->right = p;
        }
    }

    void insertImproved(T key) {
        Node<T>* p = new Node<T>;
        p->key = key;
        Node<T>* walker = this->root;
        if (walker == nullptr) {
            this->root = p;
            return;
        }
        while (walker != nullptr) {
            if (p->key < walker->key) {
                if (walker->left == nullptr) {
                    walker->left = p;
                    p->parent = walker;
                    return;
                }
                walker = walker->left;
            } else {        // The right child is non-decreasing
                if (walker->right == nullptr) {
                    walker->right = p;
                    p->parent = walker;
                    return;
                }
                walker = walker->right;
            }
        }
    }

    void createByString(std::string& string) {
        std::stringstream sStream(string);
        char keyTemp;
        while (sStream >> keyTemp) {
            insert(keyTemp);
        }
    }

    friend void createFromInAndPre (BST<char>& tree
            ,const std::string& inOrder, const std::string& preOrder);
    friend void createFromInAndPost(BST<char>& tree
            ,const std::string& inOrder, const std::string& postOrder);

};

/* Other Functions */

template<typename T>
std::istream& operator>>(std::istream& input, BST<T>& tree) {
    std::string inputString;
    std::getline(input, inputString);
    std::stringstream sStream(inputString);
    char key;
    while (sStream >> key) {
        Node<T>* temp = new Node<T>;
        temp->key = key;
        tree.insert(temp);
    }
    return input;
}

#endif
