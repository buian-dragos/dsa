#pragma once
//DO NOT INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111

struct Node {
    TComp value;
    Node* prev;
    Node* next;
};

class SortedIndexedList {
private:
	friend class ListIterator;
private:
    int _size;
    Node* head;
    Node* tail;
    Relation relation;

public:
	// constructor
	SortedIndexedList(Relation r);

	// returns the size of the list
    //Theta(1)
	int size() const;

	//checks if the list is empty
    //Theta(1)
	bool isEmpty() const;

	// returns an element from a position
	//throws exception if the position is not valid
    //BC Theta(1) WC Theta(n) AVG O(n)
	TComp getElement(int pos) const;

	// adds an element in the sortedList (to the corresponding position)
    //BC Theta(1) WC Theta(n) AVG O(n)
	void add(TComp e);

	// removes an element from a given position
	//returns the removed element
	//throws an exception if the position is not valid
    //Theta(pos)
    TComp remove(int pos);

	// searches for an element and returns the first position where the element appears or -1 if the element is not in the list
    //BC Theta(1) WC Theta(n) AVG O(n)
    int search(TComp e) const;

    void reverseBetween(int pos1, int pos2);

	// returns an iterator set to the first element of the list or invalid if the list is empty
	ListIterator iterator();

	//destructor
	~SortedIndexedList();

};
