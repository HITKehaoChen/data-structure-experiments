#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

/* data structure with concrete implementation */

template<typename T>
class arrayQueue {
private:
    T* data = new T[2];
    size_t head = 0;
    size_t tail = 0;
    size_t size = 0;
    size_t capacity = 2;
public:
    T deQueue();

    void enQueue(T);

    bool isEmpty() const;

    void enlarge();
};

template<typename T>
bool arrayQueue<T>::isEmpty() const {
    return head == tail;
}

template<typename T>
T arrayQueue<T>::deQueue() {
    if (head == tail) {
        throw std::runtime_error("Stack overflow!");
    }
    T temp = data[head];
    head = (head + 1) % capacity;
    --size;
    return temp;
}

template<typename T>
void arrayQueue<T>::enQueue(T x) {
    data[tail] = x;
    tail = (tail + 1) % capacity;
    ++size;
    if (head == tail) {
        this->enlarge();
    }
}

template<typename T>
void arrayQueue<T>::enlarge() {     // enlarge the capacity of the queue
    T* temp = new T[capacity * 2];
    for (size_t i = 0; i < size; ++i) {
        temp[i] = data[head];
        head = (head + 1) % capacity;
    }
    head = 0;
    tail = size;
    delete[] data;
    data = temp;
    capacity *= 2;
}


/* abstract data type */

template<typename T>
class adtQueue {
private:
    arrayQueue<T> q;
public:
    T deQueue() { return q.deQueue(); };

    void enQueue(T x) { q.enQueue(x); }

    bool isEmpty() const { return q.isEmpty(); };
};

#endif
