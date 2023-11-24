#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <vector>

SortedMultiMap::SortedMultiMap(Relation r) : relation(r) {
    this->capacity = 10;
    this->nodes.resize(this->capacity);
    this->len = 0;
    this->root = -1;
    this->firstEmpty = 0;
    for (int i = 0; i < capacity - 1; i++)
        this->nodes[i].right = i + 1;
    this->nodes[capacity - 1].right = -1;
}

int SortedMultiMap::allocateNode() {
    if (this->firstEmpty == -1) {
        this->capacity *= 2;
        this->nodes.resize(this->capacity);
        for (int i = this->capacity / 2; i < capacity - 1; i++)
            this->nodes[i].right = i + 1;
        this->nodes[capacity - 1].right = -1;
        this->firstEmpty = this->capacity / 2;
    }

    int newPosition = this->firstEmpty;
    this->firstEmpty = this->nodes[firstEmpty].right;
    return newPosition;
}

void SortedMultiMap::deallocateNode(int position) {
    this->nodes[position].right = this->firstEmpty;
    this->firstEmpty = position;
}

int SortedMultiMap::minimum(int position) const {
    if (position == -1)
        return -1;
    while (this->nodes[position].left != -1)
        position = this->nodes[position].left;
    return position;
}

int SortedMultiMap::maximum(int position) const {
    if (position == -1)
        return -1;
    while (this->nodes[position].right != -1)
        position = this->nodes[position].right;
    return position;
}

int SortedMultiMap::predecessor(int position) const {
    if (position == -1)
        return -1;
    if (this->nodes[position].left != -1)
        return this->maximum(this->nodes[position].left);

    int parent = this->nodes[position].right;
    while (parent != -1 && position == this->nodes[parent].left) {
        position = parent;
        parent = this->nodes[parent].right;
    }
    return parent;
}

int SortedMultiMap::successor(int position) const {
    if (position == -1)
        return -1;
    if (this->nodes[position].right != -1)
        return this->minimum(this->nodes[position].right);

    int parent = this->nodes[position].right;
    while (parent != -1 && position == this->nodes[parent].right) {
        position = parent;
        parent = this->nodes[parent].right;
    }
    return parent;
}

void SortedMultiMap::add(TKey c, TValue v) {
    len++;
    TElem element(c, v);
    if (this->root == -1) {
        int newNode = this->allocateNode();
        this->nodes[newNode].info = element;
        this->nodes[newNode].left = -1;
        this->nodes[newNode].right = -1;
        this->root = newNode;
    }
    else {
        int current = this->root;
        int parent = -1;
        while (current != -1) {
            parent = current;
            if (this->relation(element.first, this->nodes[current].info.first))
                current = this->nodes[current].left;
            else
                current = this->nodes[current].right;
        }

        if (this->relation(element.first, this->nodes[parent].info.first)) {
            int newNode = this->allocateNode();
            this->nodes[newNode].info = element;
            this->nodes[newNode].left = -1;
            this->nodes[newNode].right = -1;
            this->nodes[parent].left = newNode;
        }
        else {
            int newNode = this->allocateNode();
            this->nodes[newNode].info = element;
            this->nodes[newNode].left = -1;
            this->nodes[newNode].right = -1;
            this->nodes[parent].right = newNode;
        }
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    vector<TValue> values;
    int current = root;
    while (current != -1) {
        if (relation(c, nodes[current].info.first)) {
            current = nodes[current].left;
        }
        else if (relation(nodes[current].info.first, c)) {
            current = nodes[current].right;
        }
        else {
            int start = current;
            while (start != -1 && nodes[start].info.first == c) {
                values.push_back(nodes[start].info.second);
                start = successor(start);
            }
            return values;
        }
    }
    return values;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    TElem element(c, v);
    len--;
    int current = this->root;
    int parent = -1;
    while (current != -1 && !(this->nodes[current].info == element)) {
        parent = current;
        if (this->relation(element.first, this->nodes[current].info.first))
            current = this->nodes[current].left;
        else
            current = this->nodes[current].right;
    }

    if (current == -1)
        return false;

    if (this->nodes[current].info == element) {
        if (this->nodes[current].right == -1) {
            if (parent == -1)
                this->root = this->nodes[current].left;
            else if (this->nodes[parent].left == current)
                this->nodes[parent].left = this->nodes[current].left;
            else
                this->nodes[parent].right = this->nodes[current].left;

            this->deallocateNode(current);
        }
        else if (this->nodes[current].left == -1) {
            if (parent == -1)
                this->root = this->nodes[current].right;
            else if (this->nodes[parent].left == current)
                this->nodes[parent].left = this->nodes[current].right;
            else
                this->nodes[parent].right = this->nodes[current].right;

            this->deallocateNode(current);
        }
        else {
            int minimumRight = this->minimum(this->nodes[current].right);
            TElem minimumElement = this->nodes[minimumRight].info;

            this->nodes[current].info = minimumElement;
            this->remove(minimumElement.first, minimumElement.second);
        }

        return true;
    }

    return false;
}

int SortedMultiMap::size() const {
    return len;
}

bool SortedMultiMap::isEmpty() const {
    return this->root == -1;
}

SMMIterator SortedMultiMap::iterator() const {
    return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
    this->nodes.clear();
}
