#include "VectorDinamic.h"
#include <malloc.h>

typedef void* TElem;

Vector* createVector(int cp) {
	/*
	* The function creates a dynamically allocated Vector
	* Input data: cp - integer (starting capacity)
	* Output data: v - Vector* (pointer to the start of the allocated memory)
	*/
	Vector* v = (Vector*)malloc(sizeof(Vector));
	if (v != NULL) {
		v->capacity = cp;
		v->elements = (TElem*)malloc(cp * sizeof(TElem));
		v->size = 0;	
	}
	return v;
}

void deleteElement(Vector* v, int i, void(*destroyElement)(void*)) {
	/*
	* The function deletes an element from the Vector based on it's index
	* Input data:	v - Vector*
	*				i - integer
	* Output data:	-
	*/
	destroyElement(v->elements[i]);
	for (int j = i + 1; j < v->size; j++)
		if (j != i)
			v->elements[j - 1] = v->elements[j];
	(v->size)--;
}

void addLastElement(Vector* v, TElem e) {
	/*
	* The function adds an element at the end of the Vector
	* Input data:	v - Vector*
	*				e - Expense
	* Output data:  -
	*/
	if (v->size == v->capacity) {
		resize(v);
	}
	v->elements[(v->size)++] = e;
}

void insertElement(Vector* v, int i, TElem elem) {
	/*
	* The functions inserts an element on a certain position
	* Input data:	v - Vector*
	*				i - integer
	*				elem - void*
	* Output data: - 
	*/
	if (i >= 0 && i <= v->size) {
		if (v->size + 1 == v->capacity)
			resize(v);
		for (int j = v->size; j > i; j--)
			v->elements[j] = v->elements[j - 1];
		v->elements[i] = elem;
		v->size++;
	}
}

void resize(Vector* v) {
	/*
	* The function allocates doubles the memory of the Vector
	* Input data: v - Vector*
	* Output data: -
	*/
	if (v->capacity >= 2) {
		TElem* temp = (TElem*)malloc(2 * v->capacity * sizeof(TElem));
		for (int i = 0; i < v->size; i++)
			if (temp != NULL)
				temp[i] = v->elements[i];
		(v->capacity) *= 2;
		free(v->elements);
		v->elements = temp;
	}
}

TElem ELEMENT(Vector* v, int i) {
	/*
	* The function returns the i-th element of a Vector
	* Input data:	v - Vector*
	*				i - integer (element index)
	* Output data:	Expense (i-th expense)
	*/
	return v->elements[i - 1];
}

int length(Vector* v) {
	/*
	* The function returns the length of a Vector
	* Input data:	v - Vector*
	* Output data:	length - integer
	*/
	return v->size;
}

void reverse(Vector* v) {
	/*
	* The function reverses the order a give Vector
	* Input data:	v - Vector*
	* Output data:
	*/
	for (int i = 0; i < v->size / 2; i++)
	{
		TElem aux = v->elements[i];
		v->elements[i] = v->elements[v->size - 1 - i];
		v->elements[v->size - 1 - i] = aux;
	}
}

void destroyVector(Vector* v, void(*destroyElement)(void*)) {
	/*
	* The function destroys end frees the memory allocated for a Vector
	* Input data:	v - Vector*
	* Output data:	-
	*/
	for (int i = 0; i < v->size; i++) {
		TElem e = v->elements[i];
		destroyElement(e);
	}
	free(v->elements);
	free(v);
	
}

Iterator* createIterator(Vector* v) {
	/*
	* The function creates an iterator for a Vector
	* Input data:	v - Vector*
	* Output data:	it - Iterator* (points to the first element in the Vector)
	*/
	Iterator* it = (Iterator*)malloc(sizeof(Iterator));
	if (it != NULL) {
		it->v = v;
		it->curent = 0;
	}
	return it;
}

int validate(Iterator* it) {
	/*
	* The function checks if a iterator points to an existing element in the vecotr
	* Input data:	it - Iterator*
	* Output data:	1 - if the iterator points to a existing element
	*				0 - otherwise
	*/
	if ((it->v)->size <= it->curent)
		return 0;
	return 1;
}

void first(Iterator* it) {
	/*
	* The function sets the iterator to the first element in the Vector
	* Input data:	it - Iterator*
	* Output data:	-
	*/
	it->curent = 0;
}
// Aici posibil sa nu trebuisca paranteze but i'm not so sure idk
void next(Iterator* it) {
	/*
	* The function moves the iterator the the next element in the vecotr
	* Input data: it - Iterator*
	* Output data: -
	*/
	(it->curent)++;
}

TElem elementI(Iterator* it) {
	/*
	* The function return the element to which is pointing
	* Input data: it - Iterator*
	* Output data: Expense
	*/
	return it->v->elements[it->curent];
	// mai e varianta
	// return *(it->current);
}

void destroyIterator(Iterator* it) {
	/*
	* The function destroys an iterator and frees the memory
	* Input data: it - Iterator*
	* Output data: -
	*/
	free(it);
}