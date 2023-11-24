#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

void ListIterator::first(){
    current = list.head;
}

void ListIterator::next(){
    if (!valid()) {
        throw std::exception();
    }
    current = list.elements[current].next;
}

bool ListIterator::valid() const{
    return current != -1;
}

TComp ListIterator::getCurrent() const{
    if (!valid()) {
        throw std::exception();
    }
    return list.elements[current].info;
}


