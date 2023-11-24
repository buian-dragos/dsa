#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
#include <algorithm>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
    _size = 0;
    head = nullptr;
    tail = nullptr;
    relation = r;
}

int SortedIndexedList::size() const {
    return _size;
}

bool SortedIndexedList::isEmpty() const {
    return _size == 0;
}

TComp SortedIndexedList::getElement(int i) const{
    if (i < 0 || i >= _size) {
        throw std::exception();
    }
    int j = 0;
    Node* current = head;
    while (j < i) {
        current = current->next;
        j++;
    }
    return current->value;
}

TComp SortedIndexedList::remove(int pos) {
    if (pos < 0 || pos >= _size) {
        throw std::exception();
    }
    int i = 0;
    Node* current = head;
    while (i < pos) {
        current = current->next;
        i++;
    }
    TComp removedValue = current->value;
    if (current == head) {
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
    }
    else if (current == tail) {
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
    }
    else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }
    delete current;
    _size--;
    return removedValue;
}

int SortedIndexedList::search(TComp e) const {
    int pos = 0;
    Node* current = head;
    while (current != nullptr) {
        if (current->value == e) {
            return pos;
        }
        current = current->next;
        pos++;
    }
    return -1;
}

void SortedIndexedList::add(TComp e) {
    Node* newNode = new Node{ e, nullptr, nullptr };
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        Node* current = head;
        while (current != nullptr && relation(current->value, e)) {
            current = current->next;
        }
        if (current == nullptr) {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        else {
            if (current->prev == nullptr) {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            else {
                newNode->prev = current->prev;
                current->prev->next = newNode;
                newNode->next = current;
                current->prev = newNode;
            }
        }
    }
    _size++;
}

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

//destructor
SortedIndexedList::~SortedIndexedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void SortedIndexedList::reverseBetween(int pos1, int pos2) {
    if (pos1 < 0 || pos1 >= _size || pos2 < 0 || pos2 >= _size){
        throw std::exception();
    }
    int i = 0;
    Node* current = head;
    Node* start;
    Node* end;
    if (pos1 == 0 || pos2 == 0)
        start = head;
    while (i <= max(pos1,pos2)){
        i++;
        if (i == min(pos1,pos2)){
            start = current->next;
        }
        current = current->next;
    }
    end = current->prev;

    for (int j = 0; j < (max(pos1,pos2) - min(pos1,pos2))/2 + 1; j++){
//        std::cout << start->value << "--" << end->value << " ";
        swap(start->value,end->value);

        end = end->prev;
        start = start->next;
    }
}
