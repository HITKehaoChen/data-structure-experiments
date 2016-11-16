#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <fstream>
#include <iostream>
#include "queue.h"
#include "stack.h"

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
    bool leftFlag = false;
    bool rightFlag = false;
};

/* Tree classes */

template<typename T>
class BinaryTree {
private:
    Node<T>* root = nullptr;

    void inOrderR(Node<T>* p) const {
        if (p != nullptr) {
            inOrderR(p->left);
            std::cout << p->key << ' ';
            inOrderR(p->right);
        }
    }

    void preOrderR(Node<T>* p) const {
        if (p != nullptr) {
            std::cout << p->key << ' ';
            preOrderR(p->left);
            preOrderR(p->right);
        }
    }

    void postOrderR(Node<T>* p) const {
        if (p != nullptr) {
            postOrderR(p->left);
            postOrderR(p->right);
            std::cout << p->key << ' ';
        }
    }

    void createWithHash(std::stringstream& sStream, Node<T>* p) {
        char keyTemp;
        sStream >> keyTemp;
        if (keyTemp != '#') {
            Node<T>* nodeTemp = new Node<T>;
            nodeTemp->key = keyTemp;
            p->left = nodeTemp;
            createWithHash(sStream, p->left);
        } else {
            p->left = nullptr;
        }
        sStream >> keyTemp;
        if (keyTemp != '#') {
            Node<T>* nodeTemp = new Node<T>;
            nodeTemp->key = keyTemp;
            p->right = nodeTemp;
            createWithHash(sStream, p->right);
        } else {
            p->right = nullptr;
        }
    }

    void destroy(Node<T>* p) {
        if (p == nullptr) {
            return;
        } else {
            if (!p->leftFlag && p->left != nullptr) {
                destroy(p->left);
            }
            if (!p->rightFlag && p->right != nullptr) {
                destroy(p->right);
            }
            delete (p);
        }
    }

    void threaded(Node<T>* node) {
        if (node != nullptr) {
            if (node->left != nullptr) {
                threaded(node->left);
            } else {
                node->left = inOrderPredecessor(node);
            }
            if (node->right != nullptr) {
                threaded(node->right);
            } else {
                node->right = inOrderSuccessor(node);
            }
        }
    }

public:
    BinaryTree() : root{nullptr} {}

    ~BinaryTree() {
        destroy(root);
    }

    void inOrderWalkR() const {
        if (root != nullptr) {
            inOrderR(root->left);
            std::cout << root->key << ' ';
            inOrderR(root->right);
        }
        std::cout << std::endl;
    }

    void preOrderWalkR() const {
        if (root != nullptr) {
            std::cout << root->key << ' ';
            preOrderR(root->left);
            preOrderR(root->right);
        }
        std::cout << std::endl;
    }

    void postOrderWalkR() const {
        if (root != nullptr) {
            postOrderR(root->left);
            postOrderR(root->right);
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

    void createWithHash(std::string& string) {
        std::stringstream sStream(string);
        char keyTemp;
        sStream >> keyTemp;
        insert(keyTemp);
        createWithHash(sStream, root);
    }

    void createWithoutHash(std::string& string) {
        std::stringstream sStream(string);
        char keyTemp;
        while (sStream >> keyTemp) {
            insert(keyTemp);
        }
    }

    void preOrderWalk() const {
        adtStack<Node<T>*> stack;
        Node<T>* walker = root;
        bool isDone = false;
        while (!isDone) {
            if (walker != nullptr) {
                std::cout << walker->key << ' ';
                stack.push(walker);
                walker = walker->left;
            } else {
                if (!stack.isEmpty()) {
                    walker = stack.pop();
                    walker = walker->right;
                } else {
                    isDone = true;
                }
            }
        }
        std::cout << std::endl;
    }

    void inOrderWalk() const {
        adtStack<Node<T>*> stack;
        Node<T>* walker = root;
        bool isDone = false;
        while (!isDone) {
            if (walker != nullptr) {
                stack.push(walker);
                walker = walker->left;
            } else {
                if (!stack.isEmpty()) {
                    walker = stack.pop();
                    std::cout << walker->key << ' ';
                    walker = walker->right;
                } else {
                    isDone = true;
                }
            }
        }
        std::cout << std::endl;
    }

    void postOrderWalk() const {
        adtStack<std::pair<Node<T>*, bool>> pStack;
        T keyStack;
        Node<T>* walker = root;
        bool isDone = false;
        while (!isDone) {
            if (walker != nullptr) {
                std::pair<Node<T>*, bool> temp;
                temp.first = walker;
                temp.second = false;
                pStack.push(temp);
                walker = walker->left;
            } else {
                if (!pStack.isEmpty()) {
                    std::pair<Node<T>*, bool> temp;
                    temp = pStack.pop();
                    walker = temp.first;
                    if (!temp.second) {
                        walker = walker->right;
                        temp.second = true;
                        pStack.push(temp);
                    } else {
                        std::cout << walker->key << ' ';
                        walker = nullptr;
                    }
                } else {
                    isDone = true;
                }
            }
        }
        std::cout << std::endl;
    }

    Node<T>* inOrderSuccessor(Node<T>* p) const {
        if (p->right != nullptr && ! p->rightFlag) {
            p = p->right;
            while (! p->leftFlag && p->left != nullptr) {
                p = p->left;
            }
            return p;
        } else {
            Node<T>* walker = p;
            Node<T>* parent = p->parent;
            while (parent != nullptr && walker == parent->right) {
                walker = parent;
                parent = walker->parent;
            }
            p->rightFlag = true;
            return parent;
        }
    }

    Node<T>* inOrderPredecessor(Node<T>* p) const {
        if (p->left != nullptr) {
            p = p->left;
            while (p->right != nullptr) {
                p = p->right;
            }
            return p;
        } else {
            Node<T>* walker = p;
            Node<T>* parent = p->parent;
            while (parent != nullptr && walker == parent->left) {
                walker = parent;
                parent = walker->parent;
            }
            p->leftFlag = true;
            return parent;
        }
    }

    void getThreaded() {
        threaded(root);
    }

    Node<T>* threadedPreOrderSuccessor(Node<T>* p) const {
        if (! p->leftFlag) {
            return p->left;
        } else {
            while (p->rightFlag && p->right != nullptr) {
                p = p->right;
            }
            return p->right;
        }
    }

    Node<T>* threadedInOrderSuccessor(Node<T>* p) const {
        if (p->rightFlag) {
            return p->right;
        } else {
            return inOrderSuccessor(p);
        }
    }

    Node<T>* threadedPostOrderSuccessor(Node<T>* p) const {
        Node<T>* walker = p;
        if (p->parent == nullptr) {
            return nullptr;
        }
        if (p == p->parent->left) {
            if (inOrderSuccessor(p->parent) == nullptr) {
                return p->parent;
            } else {
                Node<T>* temp = p->parent->right;
                bool isDone = false;
                while (! isDone) {
                    while (!temp->leftFlag) {
                        temp = temp->left;
                    }
                    if (! temp->rightFlag) {
                        temp = temp->right;
                    } else {
                        isDone = true;
                    }
                }
                return temp;
            }
        } else {
            return p->parent;
        }
    }
//        Node<T>* walkerBehind = p;
//        Node<T>* walkerAhead = p->parent;
//        while (walkerAhead->rightFlag) {
//            walkerBehind = walkerAhead;
//            walkerAhead = walkerAhead->parent;
//        }
//        if (walkerBehind == walkerAhead->right) {
//            return walkerAhead;
//        } else {
//            if (inOrderSuccessor(p->right) == nullptr) {
//                return p->right;
//            } else {
//                return inOrderSuccessor(p->right);
//            }
//        }
//    }
//            if (inOrderSuccessor(p->right) == nullptr) {
//                return p->right;
//            } else {
//                return inOrderSuccessor(p->right);
//            }

    void threadPreOrderWalk() const {
        Node<T>* temp = root;
        while (temp != nullptr) {
            std::cout << temp->key << ' ';
            temp = threadedPreOrderSuccessor(temp);
        }
        std::cout << std::endl;
    }

    void threadedInOrderWalk() const {
        Node<T>* temp = root;
        while (temp != nullptr) {
            std::cout << temp->key << ' ';
            temp = threadedInOrderSuccessor(temp);
        }
        std::cout << std::endl;
    }

    void threadedPostOrderWalk() const {
        Node<T>* temp = root;
        bool isDone = false;
        while (! isDone) {
            while (!temp->leftFlag) {
                temp = temp->left;
            }
            if (! temp->rightFlag) {
                temp = temp->right;
            } else {
                isDone = true;
            }
        }
        while (temp != nullptr) {
            std::cout << temp->key << ' ';
            temp = threadedPostOrderSuccessor(temp);
        }
        std::cout << std::endl;
    }

};

/* Other Functions */

template<typename T>
std::istream& operator>>(std::istream& input, BinaryTree<T>& tree) {
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
