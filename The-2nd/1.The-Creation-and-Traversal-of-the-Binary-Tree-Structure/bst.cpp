#include <iostream>
#include <sstream>
#include "bst.h"

void BST::insert(BSTNode* newLeaf) {
    BSTNode* temp = NULL;
    BSTNode* p = head;
    while (p != NULL) {
        temp = p;
        if (newLeaf->key < p->key) {
            p = p->left;
        } else {
            p = p->right;
        }
    }
    newLeaf->parent = temp;
    if (temp == NULL) {     // if tree is empty
        head = newLeaf;
    } else if (newLeaf->key < temp->key) {
        temp->left = newLeaf;
    } else {
        temp->right = newLeaf;
    }
}

std::string BST::traversal(size_t mode, bool isRecursive) {
    if (mode != 0 && mode != 1 && mode != 2) {
        return "Bad mode number.";
    }
    std::string trail;
    if (isRecursive) {
        std::stringstream trailStream(trail);
        if (mode == 0) {
            preOrderTreeWalk(this->head, trailStream);

        } else if (mode == 1) {
            inOrderTreeWalk(this->head, trailStream);
        } else {
            postOrderTreeWalk(this->head, trailStream);
        }
    } else {
        BSTNode *p = head;
        adtStack stack;
        if (mode == 0) {

        } else if (mode == 1) {
            bool done = false;
            while (!done) {
                if (p != NULL) {
                    stack.push(p);
                    p = p->left;
                } else {
                    if (!stack.isEmpty()) {
                        p = stack.pop();
                        trail += p->key + ' ';
                        p = p->right;
                    } else {
                        done = true;
                    }
                }
            }
        } else {

        }
    }
    return trail;
}

void inOrderTreeWalk(BSTNode* p, std::stringstream& trailSteam) {
    if (p != NULL) {
        inOrderTreeWalk(p->left, trailSteam);
        trailSteam << p->key + ' ';
        inOrderTreeWalk(p->right, trailSteam);
    }
}

void preOrderTreeWalk(BSTNode* p, std::stringstream& trailSteam) {
    if (p != NULL) {
        trailSteam << p->key + ' ';
        preOrderTreeWalk(p->left, trailSteam);
        preOrderTreeWalk(p->right, trailSteam);
    }
}

void postOrderTreeWalk(BSTNode* p, std::stringstream& trailSteam) {
    if (p != NULL) {
        postOrderTreeWalk(p->left, trailSteam);
        postOrderTreeWalk(p->right, trailSteam);
        trailSteam << p->key + ' ';
    }
}
