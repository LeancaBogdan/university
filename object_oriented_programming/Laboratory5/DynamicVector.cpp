#include "DynamicVector.h"



DynamicVector::DynamicVector(int cap)
{
	this->elems = new TElem[cap];
	this->length = 0;
	this->capacity = cap;
}

DynamicVector::DynamicVector(const DynamicVector& v)
{
	this->length = v.length;
	this->capacity = v.capacity;
	this->elems = new TElem[this->capacity];
	for (int i = 0; i < this->length; i++)
		this->elems[i] = v.elems[i];
}

DynamicVector::~DynamicVector()
{
	delete[] this->elems;
}

DynamicVector& DynamicVector::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;

	this->length = v.length;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new TElem[this->capacity];
	TElem * vect = v.getAllElems();
	for (int i = 0; i < this->length; i++)
		this->elems[i] = vect[i];

	return *this;
}

DynamicVector & DynamicVector::operator+(const TElem e)
{
	this->resize();
	this->elems[length++] = e;
	return *this;
}

void DynamicVector::add(const TElem& e)
{
	this->resize();
	this->elems[this->length++] = e;
}

void DynamicVector::remove(int pos)
{
	this->resize();
	delete this->elems[pos];
	this->elems[pos] = this->elems[this->length--];
}

void DynamicVector::setElem(int pos, const TElem e)
{
	delete this->elems[pos];
	this->elems[pos] = e;
}

void DynamicVector::resize()
{
	if (this->length == this->capacity)
	{
		TElem *copy = new TElem[this->capacity * 2];
		this->capacity *= 2;
		for (int i = 0; i < this->length; i++)
			copy[i] = this->elems[i];
		delete[]this->elems;
		this->elems = copy;
	}
	else if (this->length < this->capacity / 4)
	{
		TElem *copy = new TElem[this->capacity / 4];
		this->capacity /= 4;
		for (int i = 0; i < this->length; i++)
			copy[i] = this->elems[i];
		delete[]this->elems;
		this->elems = copy;
	}
}

TElem* DynamicVector::getAllElems() const
{
	return this->elems;
}

int DynamicVector::getLength() const
{
	return this->length;
}

DynamicVector & operator+(const TElem& e, DynamicVector& v)
{
	v.add(e);
	return v;
}
