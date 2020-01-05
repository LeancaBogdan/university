#pragma once
#include "Coat.h"

typedef Coat* TElem;

class DynamicVector
{
	TElem *elems;
	int capacity;
	int length;

public:
	///<summary>
	///Creates a dynamic array of elements of type TElem
	///</summary>
	///<param cap> Integer, the capacity of the dynamic array
	DynamicVector(int cap = 10);

	///<summary>
	///Copy constructor for a DynamicVector
	///</summary>
	DynamicVector(const DynamicVector& v);
	
	///<summary>
	///Destructor for a DynamicVector
	///</summary>
	~DynamicVector();

	///<summary>
	///Overloads the assignment operator for a DynamicVector
	///</summary>
	///<param v> Another DynamicVector object</param>
	DynamicVector& operator=(const DynamicVector& v);

	///<summary>
	///Overloads the "+" operator for a DynamicVector
	///</summary>
	///<param e> An element of type TElem to be added to the DynamicVector</param>
	DynamicVector& operator+(const TElem e);

	friend DynamicVector& operator+(const TElem& e, DynamicVector& v);

	///<summary>
	///Adds an element of type TElem to the DynamicVector
	///</summary>
	///<param e> TElem, the element to be added</param>
	void add(const TElem& e);

	///<summary>
	///Removes an element from the DynamicVector by it's position
	///</summary>
	///<param pos> Integer, the position from which the element will be removed</param>
	void remove(int pos);

	///<summary>
	///Changes an element from a given position with a new element of type TElem
	///</summary>
	///<param pos> Integer, the position</param>
	///<param e> TElem, the new element</param>
	void setElem(int pos, const TElem e);

	///<summary>
	///Resizes the DynamicVector
	///</summary>
	void resize();

	///<summary>
	///Returns a list of all the elements in the DynamicVector
	///</summary>
	///<returns> Pointer to the list of TElem objects</returns>
	TElem *getAllElems() const;

	///<summary>
	///Returns the actual length of the DynamicVector
	///</summary>
	///<returns> Integer representing the length of the DynamicVector</returns>
	int getLength() const;
};

