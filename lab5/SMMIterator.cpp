#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>

SMMIterator::SMMIterator(const SortedMultiMap& map) : map(map) {
    // Initialize the iterator
    first();
}

void SMMIterator::first() {
    // Move the iterator to the first element
    if (!map.isEmpty()) {
        int current = map.root;
        while (map.nodes[current].left != -1) {
            current = map.nodes[current].left;
        }
        currentNode = current;
    }
    else {
        currentNode = -1;
    }
}

void SMMIterator::next() {
    // Move the iterator to the next element
    if (!valid())
        return;

    if (map.nodes[currentNode].right != -1) {
        // If the current node has a right child, move to its leftmost descendant
        currentNode = map.minimum(map.nodes[currentNode].right);
    }
    else {
        // Otherwise, find the first ancestor for which the current node is in its left subtree
        int parent = map.predecessor(currentNode);
        while (parent != -1 && map.nodes[currentNode].info.first > map.nodes[parent].info.first) {
            currentNode = parent;
            parent = map.predecessor(currentNode);
        }
        currentNode = parent;
    }
}

bool SMMIterator::valid() const {
    // Check if the iterator is valid (i.e., it points to a valid element)
    return currentNode != -1;
}

TElem SMMIterator::getCurrent() const {
    // Return the current element pointed by the iterator
    if (!valid())
        throw std::exception();

    return map.nodes[currentNode].info;
}