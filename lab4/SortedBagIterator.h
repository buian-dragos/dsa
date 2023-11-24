#pragma once
#include "SortedBag.h"
#include <exception>

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    int* sortedElements;   // Sorted array of elements
    int currentElement;    // Index of the current element in the sorted array

    void mergeSort(int* arr, int left, int right);
    void merge(int* arr, int left, int mid, int right);


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

