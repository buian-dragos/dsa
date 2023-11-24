#include "SortedBagIterator.h"
#include <exception>

// Constructor
SortedBagIterator::SortedBagIterator(const SortedBag& bag) : bag(bag) {
    int* allElements = new int[bag.len];
    int index = 0;

    for (int i = 0; i < bag.capacity; i++) {
        if (bag.elements[i].element != -1) {
            for (int j = 0; j < bag.elements[i].frequency; j++) {
                allElements[index] = bag.elements[i].element;
                index++;
            }
        }
    }

    mergeSort(allElements, 0, bag.len - 1);

    sortedElements = allElements;
    currentElement = 0;
}

// Destructor
//SortedBagIterator::~SortedBagIterator() {
//    delete[] sortedElements;
//}

void SortedBagIterator::mergeSort(int* arr, int left, int right) {
    if (left >= right) return;

    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void SortedBagIterator::merge(int* arr, int left, int mid, int right) {
//    int size1 = mid - left + 1;
//    int size2 = right - mid;
//
//    int* leftArr = new int[size1];
//    int* rightArr = new int[size2];
//
//    for (int i = 0; i < size1; i++)
//        leftArr[i] = arr[left + i];
//
//    for (int j = 0; j < size2; j++)
//        rightArr[j] = arr[mid + 1 + j];
//
//    int i = 0, j = 0, k = left;
//
//    while (i < size1 && j < size2) {
//        if (bag.relation(leftArr[i], rightArr[j]))
//            arr[k++] = leftArr[i++];
//        else
//            arr[k++] = rightArr[j++];
//    }
//
//    while (i < size1)
//        arr[k++] = leftArr[i++];
//
//    while (j < size2)
//        arr[k++] = rightArr[j++];
//
//    delete[] leftArr;
//    delete[] rightArr;
}

// Moves the iterator to the next element
void SortedBagIterator::next() {
    currentElement++;
}

// Returns true if the iterator is valid (points to a valid element), false otherwise
bool SortedBagIterator::valid()  {
    return currentElement < bag.len;
}

// Returns the value of the current element from the iterator
TElem SortedBagIterator::getCurrent() {
    if (!valid()) {
        return -1;
    }

    return sortedElements[currentElement];
}

void SortedBagIterator::first() {
    currentElement = 0;
}
