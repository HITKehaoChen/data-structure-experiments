#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <stdexcept>

template<typename T>
class arrayStack {
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
bool arrayStack<T>::isEmpty() const {
    return size == -1;
}

template<typename T>
void arrayStack<T>::push(T x) {
    size += 1;
    if (size + 1 > capacity) {
        T *temp = new T[capacity * 2];
        for (size_t i = 0; i < capacity; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
    }
    data[size] = x;
}

template<typename T>
T arrayStack<T>::pop() {
    if (size < 0) {
        throw std::runtime_error("Stack overflow!");
    }
    return data[size--];
}

class operatorStack {
private:
    arrayStack<char> stack;
public:
    bool isEmpty();

    void push(char);

    char pop();
};

class operandStack {
private:
    arrayStack<double> stack;
public:
    bool isEmpty();

    void push(double);

    double pop();
};

#endif
