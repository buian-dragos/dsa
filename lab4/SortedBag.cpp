#include "SortedBag.h"
#include "SortedBagIterator.h"

int SortedBag::hash1(TComp e) const {
    return abs(e) % capacity;
}

int SortedBag::hash2(TComp e) const {
    return abs(e) % (capacity - 1) + 1;
}

void SortedBag::resize() {
    int newCapacity = capacity * 2;
    Node* newElements = new Node[newCapacity];

    for (int i = 0; i < capacity; i++) {
        if (elements[i].element != -1) {
            int index = hash1(elements[i].element);

            while (newElements[index].element != -1) {
                index = (index + hash2(elements[i].element)) % newCapacity;
            }

            newElements[index] = elements[i];
        }
    }

    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
}

// Constructor
SortedBag::SortedBag(Relation r) {
    capacity = 16;              // Initial capacity of the hashtable
    len = 0;                   // Initialize the size to 0
    relation = r;
    elements = new Node[capacity];
}

// Adds an element to the sorted bag
void SortedBag::add(TComp e) {
    if (len >= capacity / 2)
        resize();

    int index = hash1(e);

    while (elements[index].element != -1 && elements[index].element != e) {
        index = (index + hash2(e)) % capacity;
    }

    if (elements[index].element == e) {
        elements[index].frequency++;
    } else {
        elements[index].element = e;
        elements[index].frequency = 1;
        len++;
    }
}

// Removes one occurrence of an element from the sorted bag
// Returns true if an element was removed, false otherwise
bool SortedBag::remove(TComp e) {
    int index = hash1(e);

    while (elements[index].element != -1) {
        if (elements[index].element == e) {
            if (elements[index].frequency > 1) {
                elements[index].frequency--;
            } else {
                elements[index].element = -1;
                len--;
            }

            return true;
        }

        index = (index + hash2(e)) % capacity;
    }

    return false;
}

// Checks if an element appears in the sorted bag
bool SortedBag::search(TComp e) const {
    int index = hash1(e);

    while (elements[index].element != -1) {
        if (elements[index].element == e) {
            return true;
        }

        index = (index + hash2(e)) % capacity;
    }

    return false;
}

// Returns the number of occurrences for an element in the sorted bag
int SortedBag::nrOccurrences(TComp e) const {
    int index = hash1(e);

    while (elements[index].element != -1) {
        if (elements[index].element == e) {
            return elements[index].frequency;
        }

        index = (index + hash2(e)) % capacity;
    }

    return 0;
}

// Returns the number of elements in the sorted bag
int SortedBag::size() const {
    return len;
}

// Returns an iterator for this sorted bag
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

// Checks if the sorted bag is empty
bool SortedBag::isEmpty() const {
    return len == 0;
}

// Destructor
SortedBag::~SortedBag() {
}