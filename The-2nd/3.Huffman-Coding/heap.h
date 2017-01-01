#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <utility>
#include <limits>

template<typename T>
class MinHeap {
private:
    T* data = new T[1];
    std::size_t size = 0;
    std::size_t length = 1;

    void enLarge() {
        T* temp = new T[length * 2];
        for (std::size_t i = 0; i < length; ++i) {
            temp[i] = data[i];
        }
        delete[] data;
        data = temp;
        length *= 2;
    }

    std::size_t left(std::size_t i) const {
        return 2 * i + 1;
    }

    std::size_t right(std::size_t i) const {
        return 2 * i + 2;
    }

    std::size_t parent(std::size_t i) const {
        if (i == 0) {
            throw std::runtime_error("No parent!");
        }
        return (i - 1) / 2;
    }

    void MinHeapify(std::size_t i) {
        std::size_t l = left(i);
        std::size_t r = right(i);
        T smallest;
        smallest = i;
        if (l <= size && data[l] < data[smallest]) {
            smallest = l;
        }
        if (r <= size && data[r] < data[smallest]) {
            smallest = r;
        }
        if (smallest != i) {
            using std::swap;
            swap(data[smallest], data[i]);
            MinHeapify(smallest);
        }
    }

public:
    MinHeap() {}

    MinHeap(const MinHeap& src) {
        length = src.length;
        size = src.size;
        data = new T[length];
        for (std::size_t i = 0; i < length; ++i) {
            data[i] = src.data[i];
        }
    }

    MinHeap& operator=(const MinHeap& src) {
        if (&src == this) {
            return *this;
        }
        delete[] data;
        length = src.length;
        size = src.size;
        data = new T[length];
        for (std::size_t i = 0; i < length; ++i) {
            data[i] = src.data[i];
        }
        return *this;
    }

    ~MinHeap() {
        delete[] data;
    }

    T min() const {
        return data[0];
    }

    T extractMin() {
        if (size < 1) {
            throw std::runtime_error("Heap underflow!");
        }
        T min = data[0];
        data[0] = data[size - 1];
        --size;
        MinHeapify(0);
        return min;
    }

    void decreaseKey(std::size_t index, T key) {
        if (key > data[index]) {
            throw std::runtime_error("New key is bigger than current key!");
        }
        data[index] = key;
        std::size_t i = index;
        while (i > 0 && data[parent(i)] > data[i]) {
            using std::swap;
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void insert(T key) {
        if (size == length) {
            enLarge();
        }
        ++size;
        data[size - 1] = std::numeric_limits<T>::max();
        decreaseKey(size - 1, key);
    }

};

#endif