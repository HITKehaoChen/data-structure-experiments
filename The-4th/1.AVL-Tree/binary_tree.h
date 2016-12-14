#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include "queue.h"
#include "stack.h"

/* Node classes */

template<typename T>
struct Node {
    T key = 0;
    Node* parent = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;
    int degree = 0;
};

/* Tree classes */

template<typename T>
class BinaryTree {
private:
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
            delete (p);
        }
    }

    // replace one subtree as a child of its parent with another subtree
    void transplant(Node<T>* old, Node<T>* another) {
        if (old->parent == nullptr) {
            root = another;
        } else if (old->parent->left == old) {
            old->parent->left = another;
        } else {
            old->parent->right = another;
        }
        if (another != nullptr) {
            another->parent = old;
        }
    }

protected:
    Node<T>* root = nullptr;
public:
    BinaryTree() : root{nullptr} {}

    ~BinaryTree() {
        destroy(root);
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

    virtual Node<T>* insert(T key) {
        Node<T>* p = new Node<T>;
        p->key = key;
        Node<T>* predecessor = nullptr;
        Node<T>* walker = root;
        while (walker != nullptr) {
            predecessor = walker;
            if (p->key < walker->key) {
                walker = walker->left;
            } else {        // The right child is non-decreasing.
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
        return p;
    }

    virtual Node<T>* insertImproved(T key) {
        Node<T>* p = new Node<T>;
        p->key = key;
        Node<T>* walker = this->root;
        if (walker == nullptr) {
            this->root = p;
            return p;
        } else {
            while (walker != nullptr) {
                if (p->key < walker->key) {
                    if (walker->left == nullptr) {
                        walker->left = p;
                        p->parent = walker;
                        return p;
                    }
                    walker = walker->left;
                } else {        // The right child is non-decreasing.
                    if (walker->right == nullptr) {
                        walker->right = p;
                        p->parent = walker;
                        return p;
                    }
                    walker = walker->right;
                }
            }
            return p;
        }
    }

    Node<T>* search(T key) const {
        Node<T>* walker = root;
        if (walker == nullptr || walker->key == key) {
            return walker;
        } else {
            while (walker != nullptr) {
                if (key > walker->key) {
                    walker = walker->right;
                } else if (key < walker->key) {
                    walker = walker->left;
                } else {
                    break;
                }
            }
            return walker;
        }
    }

    Node<T>* inOrderSuccessor(Node<T>* p) const {
        if (p->right != nullptr) {
            p = p->right;
            while (p->left != nullptr) {
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
            return parent;
        }
    }

    virtual Node<T>* remove(Node<T>* x) {
        Node<T>* newNode = nullptr;
        if (x->left == nullptr) {
            if (x->right == nullptr) {
                newNode = x->parent;
            } else {
                newNode = x->right;
            }
            transplant(x, x->right);
            delete x;
        } else if (x->right == nullptr) {
            newNode = x->left;
            transplant(x, x->left);
            delete x;
        } else {
            Node<T>* successor = inOrderSuccessor(x);
            if (successor->parent != x) {
                transplant(successor, successor->right);
                successor->right = x->right;
                x->right->parent = successor;
            }
            transplant(x, successor);
            successor->left = x->left;
            x->left->parent = successor;
            delete x;
            newNode = successor;
        }
        return newNode;
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
};

template<typename T>
class AVLTree : public BinaryTree<T> {
private:
    int height = 0;

    Node<T>* getHigherSubTree(Node<T>* p) {
        int leftHeight = 0;
        int rightHeight = 0;
        if (p->left != nullptr) {
            leftHeight = p->left->height;
        }
        if (p->right != nullptr) {
            rightHeight = p->right->height;
        }
        if (leftHeight > rightHeight) {
            return p->left;
        } else {
            return p->right;
        }
    }

    int getBalanceFactor(Node<T>* x) const {
        if (x == nullptr) {
            return 0;
        }
        int leftHeight;
        int rightHeight;
        if (x->left == nullptr) {
            leftHeight = 0;
        } else {
            leftHeight = x->left->height;
        }
        if (x->right == nullptr) {
            rightHeight = 0;
        } else {
            rightHeight = x->right->height;
        }
        return leftHeight - rightHeight;
    }

    int updateHeights(Node<T>* x) {
        if (x == nullptr) {
            return 0;
        } else {
            int leftHeight = updateHeights(x->left);
            int rightHeight = updateHeights(x->right);
            int larger = (leftHeight > rightHeight) ? leftHeight : rightHeight;
            x->height = larger + 1;
            return x->height;
        }
    }

    void rightRotate(Node<T>* grandfather) {
        Node<T>* father = grandfather->left;
        Node<T>* rightChild = father->right;

        // Preserve the 'father of grandfather' and Splice.
        Node<T>* temp = grandfather->parent;
        father->parent = temp;
        if (temp != nullptr) {
            if (grandfather == temp->left) {
                temp->left = father;
            } else {
                temp->right = father;
            }
        } else {
            BinaryTree<T>::root = father;
        }

        // Rotate.
        father->right = grandfather;
        grandfather->parent = father;
        grandfather->left = rightChild;
        if (rightChild != nullptr) {
            rightChild->parent = grandfather;
        }
    }

    void leftRotate(Node<T>* grandfather) {
        Node<T>* father = grandfather->right;
        Node<T>* leftChild = father->left;

        // Preserve the 'father of grandfather' and Splice.
        Node<T>* temp = grandfather->parent;
        father->parent = temp;
        if (temp != nullptr) {
            if (grandfather == temp->left) {
                temp->left = father;
            } else {
                temp->right = father;
            }
        } else {
            BinaryTree<T>::root = father;
        }

        // Rotate
        father->left = grandfather;
        grandfather->parent = father;
        grandfather->right = leftChild;
        if (leftChild != nullptr) {
            leftChild->parent = grandfather;
        }
    }

    void printGivenLevel(Node<T>* x, std::size_t level) const {
        if (x == nullptr) {
            return;
        }
        if (level == 1) {
            std::cout << x->key << ' ';
        } else {
            printGivenLevel(x->left, level - 1);
            printGivenLevel(x->right, level - 1);
        }
    }

public:
    virtual Node<T>* insert(T key) override {
        // Normal BST insertion.
        Node<T>* child = BinaryTree<T>::insert(key);

        // Update the height of the root.
        height = updateHeights(BinaryTree<T>::root);

        // Maintain AVL tree.
        Node<T>* father = child->parent;
        if (father != nullptr) {
            Node<T>* grandfather = nullptr;
            grandfather = father->parent;
            if (grandfather != nullptr) {
                while (grandfather != nullptr
                       && getBalanceFactor(grandfather) <= 1
                       && getBalanceFactor(grandfather) >= -1) {
                    grandfather = grandfather->parent;
                    father = father->parent;
                    child = child->parent;
                }
                if (grandfather != nullptr) {
                    getBalanced(grandfather, father, child);
                }

                // Update again.
                height = updateHeights(BinaryTree<T>::root);
            }
        }
        return child;
    }

    virtual Node<T>* remove(Node<T>* x) {
        bool isLeftChild = (x == x->left);
        Node<T>* temp = BinaryTree<T>::remove(x);
        updateHeights(BinaryTree<T>::root);

        // Maintain AVL tree.
        while (temp != nullptr
               && getBalanceFactor(temp) <= 1
               && getBalanceFactor(temp) >= 1) {
            temp = temp->parent;
        }
        if (temp != nullptr) {
            Node<T>* grandfather = temp;
            Node<T>* father = nullptr;
            Node<T>* child = nullptr;
            father = getHigherSubTree(grandfather);
            child = getHigherSubTree(father);
            getBalanced(grandfather, father, child);
            updateHeights(BinaryTree<T>::root);
        }
        return nullptr;
    }

    // Balance the tree.
    void getBalanced(Node<T>* grandfather, Node<T>* father, Node<T>* child) {
        if (getBalanceFactor(grandfather) > 1
            && child->key < father->key) {

            rightRotate(grandfather);
        } else if (getBalanceFactor(grandfather) > 1
                   && child->key > father->key) {

            leftRotate(father);
            rightRotate(grandfather);
        } else if (getBalanceFactor(grandfather) < -1
                   && child->key > father->key) {

            leftRotate(grandfather);
        } else if (getBalanceFactor(grandfather) < -1
                   && child->key < father->key) {

            rightRotate(father);
            leftRotate(grandfather);
        }
    }

    // A utility function to print the tree more visually.
    void levelPrint() const {
        for (std::size_t i = 1; i <= height; ++i) {
            printGivenLevel(BinaryTree<T>::root, i);
            std::cout << std::endl;
        }
    }
};

#endif
