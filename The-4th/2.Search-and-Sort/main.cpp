#include <iostream>
#include <random>
#include <utility>
//#include <stdexcept>

void BubbleSort(std::vector<int>::iterator begin, std::vector<int>::iterator end);

std::vector<int>::iterator PartitionOfQuickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end);

void QuickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end);

std::vector<int>::const_iterator BinarySearch(const std::vector<int>& container, int dest);

int main() {
    std::cout << "Please denote the num of random numbers:" << std::endl;
    std::size_t numOfRandNum = 0;
    std::cin >> numOfRandNum;
    std::cout << "Please denote the range of random numbers:" << std::endl;
    std::cout << "From:";
    int rangeFrom = 0;
    std::cin >> rangeFrom;
    std::cout << "To:";
    int rangeTo = 0;
    std::cin >> rangeTo;

    // Create n random numbers and store them in an array
    std::random_device randDev;
    std::mt19937 randGenerator(randDev());
    std::uniform_int_distribution<int> dist(rangeFrom, rangeTo);
    std::vector<int> randNums(numOfRandNum);
    auto randIter = randNums.begin();
    for (std::size_t i = 0; i < numOfRandNum; ++i) {
        (*randIter) = dist(randGenerator);
        ++randIter;
    }

    // Perform two types of sort
    std::cout << std::endl
              << "Select a kind of sort algorithm:" << std::endl
              << "  1. BubbleSort" << std::endl
              << "  2. QuickSort"
              << std::endl;
    std::string sortName = "";
    std::size_t sortType = 0;
    while (true) {
        std::cin >> sortType;
        if (sortType == 1) {
            // BubbleSort
            sortName = "BubbleSort";
            BubbleSort(randNums.begin(), randNums.end());
            break;
        } else if (sortType == 2) {
            // QuickSort
            sortName = "QuickSort";
            QuickSort(randNums.begin(), randNums.end());
            break;
        } else {
            std::cout << "Bad input!" << std::endl;
        }
    }
    std::cout << std::endl << "The result of " << sortName << " is:"
              << std::endl;
    for (auto randIter = randNums.begin(); randIter != randNums.end(); ++randIter) {
        std::cout << (*randIter) << " ";
    }

    std::cout << std::endl;

    // Binary Search
    std::cout << std::endl << "Input a number to search"
              << std::endl;
    int queryNum;
    std::cin >> queryNum;
    auto searchedNum = BinarySearch(randNums, queryNum);
    std::cout << "The number you requested is:"
              << *searchedNum << std::endl
              << "And the address is:"
              << &(*searchedNum) << std::endl;

    return 0;
}

void BubbleSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    std::vector<int>::iterator temp;
    bool sorted;
    do {
        sorted = true;
        temp = begin;
        while (temp != std::prev(end)) {
            std::vector<int>::iterator next = std::next(temp);
            if (*temp > *next) {
                using std::swap;
                swap(*temp, *next);
                sorted = false;
                ++temp;
            } else {
                ++temp;
            }
        }
    } while (!sorted);
}

std::vector<int>::iterator PartitionOfQuickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    int pivot = *begin;
    auto low = begin;
    auto high = std::prev(end);
    while (true) {
        while (*low < pivot) {
            ++low;
        }
        while (*high > pivot) {
            --high;
        }
        if (*low == pivot && *high == pivot) {
            ++low;
        }
        if (high <= low) {
            return high;
        }
        using std::swap;
        std::swap(*low, *high);
    }
}

void QuickSort(std::vector<int>::iterator begin, std::vector<int>::iterator end) {
    if (begin < end) {
        std::vector<int>::iterator pivot;
        pivot = PartitionOfQuickSort(begin, end);
        QuickSort(begin, pivot);
        QuickSort(pivot + 1, end);
    }
}

std::vector<int>::const_iterator BinarySearch(const std::vector<int>& container, int dest) {
    auto low = container.begin();
    auto high = std::prev(container.end());
    while (true) {
        auto mid = low + ((high - low) / 2);
        if (low >= high && *mid != dest) {
            throw std::runtime_error("BinarySearch Failed!");
        }
        if (*mid < dest) {
            low = mid + 1;
        } else if (*mid > dest) {
            high = mid - 1;
        } else if (*mid == dest) {
            return mid;
        }
    }
}
