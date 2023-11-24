#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
    struct Node {
        TElem info;
        int left;
        int right;
    };

    std::vector<Node> nodes;
    int root;
    Relation relation;
    int firstEmpty;
    int capacity;
    int len;

    int allocateNode();
    void deallocateNode(int position);
    int minimum(int position) const;
    int maximum(int position) const;
    int predecessor(int position) const;
    int successor(int position) const;


public:

    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};



//add:
//BC: Theta(log n)
//WC: Theta(log n)
//AVG: Theta(log n)
//
//search:
//BC: Theta(log n)
//WC: O(n)
//AVG: O(n)
//
//remove:
//BC: Theta(log n)
//WC: O(n)
//AVG: O(n)


