#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
    const SortedIteratedList& list;
    int current;

    ListIterator(const SortedIteratedList& list) : list(list), current(list.head) {}

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;
};


