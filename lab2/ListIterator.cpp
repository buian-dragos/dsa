#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
    current = list.head;}

void ListIterator::first(){
    current = list.head;
}

void ListIterator::next(){
    if (valid()) {
        current = current->next;
    }
    else {
        throw std::exception();
    }
}

bool ListIterator::valid() const{
    return current != nullptr;
}

TComp ListIterator::getCurrent() const{
    if (valid()) {
        return current->value;
    }
    else {
        throw std::out_of_range("Invalid iterator position!");
    }
}


