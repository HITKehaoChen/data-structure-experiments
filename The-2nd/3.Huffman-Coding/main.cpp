#include <iostream>
#include "heap.h"

int main() {
    MinHeap<int> heapTest;
    heapTest.insert(6);
    heapTest.insert(3);
    heapTest.insert(89);
    heapTest.insert(1);
    heapTest.insert(4);
    for (std::size_t i = 0; i < 5; ++i) {
        std::cout << heapTest.extractMin() << std::endl;
    }
    return 0;
}
