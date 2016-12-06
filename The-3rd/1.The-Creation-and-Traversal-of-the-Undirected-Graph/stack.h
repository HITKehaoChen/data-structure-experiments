#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>

/* data structure with concrete implementation */

template<typename T>
class stackArray {
private:
    T *data = new T[1];
    int size = -1;
    size_t capacity = 1;
public:
    bool isEmpty() const;

    void push(T);

    T pop();
};

template<typename T>
bool stackArray<T>::isEmpty() const {
    return size == -1;
}

template<typename T>
void stackArray<T>::push(T x) {
    size += 1;
    if (size + 1 > capacity) {          // avoid stack overflow.
        T *temp = new T[capacity * 2];
        for (size_t i = 0; i < capacity; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        capacity *= 2;
    }
    data[size] = x;
}

template<typename T>
T stackArray<T>::pop() {
    if (size < 0) {
        throw std::runtime_error("Stack overflow!");
    }
    return data[size--];
}

/* abstract data type */

template <typename T>
class stackADT {
private:
    stackArray<T> stack;
public:
    bool isEmpty() { return stack.isEmpty(); };

    void push(T x) { stack.push(x); };

    T pop() { return stack.pop(); };
};

#endif
