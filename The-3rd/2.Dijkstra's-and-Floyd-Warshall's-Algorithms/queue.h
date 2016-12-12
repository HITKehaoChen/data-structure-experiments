#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

/* Data Structure with Concrete Implementations */

template<typename T>
class queueArray {
private:
    T* data = new T[2];
    std::size_t head = 0;
    std::size_t tail = 0;
    std::size_t size = 0;
    std::size_t capacity = 2;
public:
    T deQueue() {
        if (head == tail) {
            throw std::runtime_error("Stack overflow!");
        }
        T temp = data[head];
        head = (head + 1) % capacity;
        --size;
        return temp;
    }

    void enQueue(T x) {
        data[tail] = x;
        tail = (tail + 1) % capacity;
        ++size;
        if (head == tail) {
            enlarge();
        }
    }

    bool isEmpty() const {
        return head == tail;
    }

    void enlarge() {
        T* temp = new T[capacity * 2];
        for (std::size_t i = 0; i < size; ++i) {
            temp[i] = data[head];
            head = (head + 1) % capacity;
        }
        head = 0;
        tail = size;
        delete[] data;
        data = temp;
        capacity *= 2;
    }

    std::size_t length() const { return size; }
};

/* Abstract Data Type */

template<typename T>
class Queue {
private:
    queueArray<T> q;
public:
    T deQueue() { return q.deQueue(); }

    void enQueue(T x) { q.enQueue(x); }

    bool isEmpty() const { return q.isEmpty(); }
    
    std::size_t length() const { return q.length(); }
};

#endif
