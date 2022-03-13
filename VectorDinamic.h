#pragma once

typedef void* TElem;

typedef struct {
	TElem* elements;
	int size; // current length
	int capacity; // maximum actual capacity
}Vector;

typedef struct {
	Vector* v;
	int curent; // first position
}Iterator;


// Vector

Vector* createVector(int); // constructor
void destroyVector(Vector* v, void(*)(void*)); // destructor
int length(Vector* v); // size of Vector 
TElem ELEMENT(Vector* v, int); // the i-th element
void addLastElement(Vector*, TElem); // add an element at the back of the list)
void resize(Vector*); // enlarges the Vector
void deleteElement(Vector* v, int i, void(*destroyElement)(void*)); // delete the i-th element
void reverse(Vector*); // reverses the order of the elements
void insertElement(Vector*, int, TElem); // insert an element in the i-th position

// ITERATOR

Iterator* createIterator(Vector*); // constructor
void destroyIterator(Iterator* it); // destructor
void first(Iterator*); // selects the first element
void next(Iterator* it); // moves to the next element
TElem elementI(Iterator* it); // returns the Expense to which it points
int validate(Iterator* it); // checks if the iterator still points to an existing element
