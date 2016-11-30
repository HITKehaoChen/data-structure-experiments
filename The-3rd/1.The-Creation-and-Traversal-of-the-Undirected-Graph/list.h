#ifndef LIST_H
#define LIST_H

template <typename T>
struct NodeLinked {
    T key;
    NodeLinked* next = nullptr;
    NodeLinked* prev = nullptr;
};

template <typename T>
class ListLinked {
private:
    NodeLinked<T>* nil = nullptr;
public:
    ListLinked() {
        nil = new NodeLinked<T>;
        nil->next = nil;
        nil->prev = nil;
    }

    ~ListLinked() {
        NodeLinked<T>* walker = nil->next;
        while (walker != nil) {
            NodeLinked<T>* temp = walker;
            delete temp;
            walker = walker->next;
        }
        delete nil;
    }

    void insert(NodeLinked<T>* x) {
        nil->next->prev = x;
        x->next = nil->next;
        x->prev = nil;
        nil->next = x;
    }

    void remove(NodeLinked<T>* x) {
        x->next->prev = x->prev;
        x->prev->next = x->next;
        delete x;
    }

    NodeLinked<T>* search(T x) const {
        NodeLinked<T>* walker = nil->next;
        while (walker != nil && walker->key != x) {
            walker = walker->next;
        }
        if (walker->key == x) {
            return walker;
        } else {
            return nullptr;
        }
    }
};

#endif
