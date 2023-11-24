#include "SortedIteratedList.h"
#include "ListIterator.h"
#include <iostream>
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    relation = r;
    capacity = 10;
    elements = new Node[capacity];
    head = -1;
    tail = -1;
    firstEmpty = 0;
    count = 0;

    for (int i = 0; i < capacity - 1; i++) {
        elements[i].next = i + 1;
        elements[i + 1].prev = i;
    }

    elements[capacity - 1].next = -1;
    elements[0].prev = -1;
}

int SortedIteratedList::size() const {
    return count;
}

bool SortedIteratedList::isEmpty() const {
    return count == 0;
}

ListIterator SortedIteratedList::first() const {
    return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator pos) const {
    if (!pos.valid())
        throw std::exception();

    return elements[pos.current].info;
}

void SortedIteratedList::add(TComp e) {
    if (count == capacity)
        resize();

    int current = head;
    int prev = -1;

    while (current != -1 && relation(elements[current].info, e)) {
        prev = current;
        current = elements[current].next;
    }

    int newElem = firstEmpty;
    firstEmpty = elements[firstEmpty].next;

    elements[newElem].info = e;
    elements[newElem].next = current;
    elements[newElem].prev = prev;

    if (prev != -1)
        elements[prev].next = newElem;
    else
        head = newElem;

    if (current != -1)
        elements[current].prev = newElem;
    else
        tail = newElem;

    count++;
}

TComp SortedIteratedList::remove(ListIterator& pos) {
    if (!pos.valid())
        throw std::exception();

    int current = pos.current;

    if (elements[current].prev != -1)
        elements[elements[current].prev].next = elements[current].next;
    else
        head = elements[current].next;

    if (elements[current].next != -1)
        elements[elements[current].next].prev = elements[current].prev;
    else
        tail = elements[current].prev;

    int next = elements[current].next;
    elements[current].next = firstEmpty;
    elements[current].prev = -1;
    firstEmpty = current;

    count--;

    pos.current = next;

    return elements[current].info;
}

ListIterator SortedIteratedList::search(TComp e) const {
    ListIterator pos(*this);

    while (pos.valid() && pos.getCurrent() != e)
        pos.next();

    return pos;
}

SortedIteratedList::~SortedIteratedList() {
    delete[] elements;
}

void SortedIteratedList::resize() {
    int newCapacity = capacity * 2;
    Node* newElements = new Node[newCapacity];

    for (int i = 0; i < capacity; i++)
        newElements[i] = elements[i];

    for (int i = capacity; i < newCapacity - 1; i++) {
        newElements[i].next = i + 1;
        newElements[i + 1].prev = i;
    }

    newElements[newCapacity - 1].next = -1;
    newElements[capacity].prev = -1;

    delete[] elements;
    elements = newElements;
    firstEmpty = capacity;

    capacity = newCapacity;
}

ListIterator SortedIteratedList::lastIndexOf(TComp e) {
    ListIterator pos(*this);
    ListIterator last(*this);

    bool found = false;

    while (true) {
        try {
            pos.next();
            if (pos.getCurrent() == e) {
                last.current = pos.current;
                found = true;
            }
        } catch (std::exception&) {
            break;
        }
    }

    if (!found)
        last.current = -1;

    return last;
}
