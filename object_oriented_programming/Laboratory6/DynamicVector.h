#pragma once
#include "Coat.h"

template <typename T>

class DynamicVector
{
	T *elems;
	unsigned int capacity;
	unsigned int length;

public:		
	/// <summary>
	/// Initializes a new instance of the <see cref="DynamicVector"/> class.
	/// </summary>
	/// <param name="cap">The capacity, 10 by default.</param>
	DynamicVector(unsigned int cap = 10);
	
	/// <summary>
	/// Copy constructor for the <see cref="DynamicVector"/> class.
	/// </summary>
	/// <param name="v">The dynamic vector to be copied.</param>
	DynamicVector(const DynamicVector &v);
		
	/// <summary>
	/// Finalizes an instance of the <see cref="DynamicVector"/> class.
	/// </summary>
	~DynamicVector();
	
	/// <summary>
	/// Operator=s the specified dynamic vector.
	/// </summary>
	/// <param name="v">The vdynamic vector.</param>
	/// <returns></returns>
	DynamicVector& operator=(const DynamicVector &v);
	
	/// <summary>
	/// Operator+s the specified element to be added.
	/// </summary>
	/// <param name="e">The element to be added.</param>
	/// <returns></returns>
	DynamicVector &operator+(const T &e);

	///<summary>
	///Overloads the "+" operator for a DynamicVector
	///</summary>
	///<param e> Element of type T to be added to the DynamicVector</param>
	///<param v> DynamicVector to which e will be added</param>
	///<return> The updated DynamicVector</return>
	friend DynamicVector& operator+(const T& e, DynamicVector& v);
	
	/// <summary>
	/// Adds the specified element e to the dynamic vector.
	/// </summary>
	/// <param name="e">The eelement to be added.</param>
	void add(const T &e);
	
	/// <summary>
	/// Removes the element on the specified position.
	/// </summary>
	/// <param name="pos">The position.</param>
	void remove(int const &pos);
	
	/// <summary>
	/// Sets the given element e on position pos.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <param name="e">The e.</param>
	void setElem(int const &pos, const T &e);
	
	/// <summary>
	/// Resizes this instance.
	/// </summary>
	void resize();
	
	/// <summary>
	/// Gets all elements.
	/// </summary>
	/// <returns></returns>
	T * getAllElems() const;
	
	/// <summary>
	/// Gets the length.
	/// </summary>
	/// <returns></returns>
	int getLength() const;

};


template <typename T>
DynamicVector<T>::DynamicVector(unsigned int cap)
{
	this->elems = new T[cap];
	this->length = 0;
	this->capacity = cap;
}

template <typename T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &v)
{
	this->length = v.length;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->length; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
DynamicVector<T> &DynamicVector<T>::operator=(const DynamicVector<T> &v)
{
	if (this == &v)
		return *this;

	this->length = v.length;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	T * vect = v.getAllElems();
	for (int i = 0; i < this->length; i++)
		this->elems[i] = vect[i];

	return *this;
}

template <typename T>
DynamicVector<T> & DynamicVector<T>::operator+(const T &e)
{
	this->resize();
	this->elems[length++] = e;
	return *this;
}

template <typename T>
void DynamicVector<T>::add(const T &e)
{
	this->resize();
	this->elems[this->length++] = e;
}

template <typename T>
void DynamicVector<T>::remove(int const &pos)
{
	this->resize();
	delete this->elems[pos];
	this->elems[pos] = this->elems[this->length-1];
	this->length--;
}

template <typename T>
void DynamicVector<T>::setElem(int const &pos, const T &e)
{
	delete this->elems[pos];
	this->elems[pos] = e;
}

template <typename T>
void DynamicVector<T>::resize()
{
	if (this->length == this->capacity)
	{
		T *copy = new T[this->capacity * 2];
		this->capacity *= 2;
		for (unsigned int i = 0; i < this->length; i++)
			copy[i] = this->elems[i];
		delete[]this->elems;
		this->elems = copy;
	}
	else if (this->length < this->capacity / 4)
	{
		T *copy = new T[this->capacity / 4];
		this->capacity /= 4;
		for (unsigned int i = 0; i < this->length; i++)
			copy[i] = this->elems[i];
		delete[] this->elems;
		this->elems = copy;
	}
}

template <typename T>
T * DynamicVector<T>::getAllElems() const
{
	return this->elems;
}

template <typename T>
int DynamicVector<T>::getLength() const
{
	return this->length;
}

template <typename T>
DynamicVector<T> & operator+(T const &e, DynamicVector<T> &v)
{
	v.add(e);
	return v;
}
