#include "Coat.h"



Coat::Coat(int size, std::string color, int price, int quant, std::string link)
{
	this->size = size;
	this->color = color;
	this->price = price;
	this->quant = quant;
	this->link = link;
}


Coat::~Coat()
{
}

int Coat::getSize()
{
	return this->size;
}

std::string Coat::getColor()
{
	return this->color;
}

int Coat::getPrice()
{
	return this->price;
}

int Coat::getQuant()
{
	return this->quant;
}

std::string Coat::getLink()
{
	return this->link;
}

void Coat::setSize(int size)
{
	this->size = size;
}

void Coat::setColor(std::string color)
{
	this->color = color;
}

void Coat::setPrice(int price)
{
	this->price = price;
}

void Coat::setQuant(int quant)
{
	this->quant = quant;
}

void Coat::setLink(std::string link)
{
	this->link = link;
}

bool Coat::operator==(Coat c2)
{
	if (this->link == c2.getLink())
		return true;
	return false;
}
/*
DynamicVector & Coat::operator+(DynamicVector v)
{
	v = v + this;
	return v;
}
*/

