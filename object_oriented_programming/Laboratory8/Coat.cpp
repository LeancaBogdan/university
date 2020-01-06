#include "Coat.h"
#include <Windows.h>
#include <shellapi.h>
#include <vector>

Coat::Coat() : price{ 0 }, quantity{ 0 }, size{ 0 }, colour{""}, photo{""}
{
}

Coat::Coat(const Coat & c)
	: price{ c.price }, quantity{ c.quantity }, size{ c.size }, colour{c.colour}, photo{c.photo}
{
}

Coat::Coat(const unsigned int & size, const std::string & colour, const unsigned int & price, const unsigned int & quantity, const std::string & photo)
	: size{ size }, colour{colour}, price{price}, quantity{quantity}, photo{photo}
{
}

Coat::~Coat()
{
}

bool Coat::operator==(const Coat & c)
{
	if (this->colour == c.colour && this->size == c.size)
		return true;
	return false;
}

Coat & Coat::operator=(const Coat & c)
{
	this->price = c.price;
	this->quantity = c.quantity;
	this->photo = c.photo;
	this->size = c.size;
	this->colour = c.colour;
	return *this;
}

void Coat::setSize(const unsigned int & size)
{
	this->size = size;
}

void Coat::setColour(const std::string & colour)
{
	this->colour = colour;
}

void Coat::setPrice(const unsigned int & price)
{
	this->price = price;
}

void Coat::setQuantity(const unsigned int & quantity)
{
	this->quantity = quantity;
}

void Coat::increaseQuantity()
{
	this->quantity++;
}

void Coat::decreaseQuantity()
{
	this->quantity--;
}

void Coat::setPhoto(const std::string & photo)
{
	this->photo = photo;
}

void Coat::showPhoto()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhoto().c_str(), NULL, SW_SHOWMAXIMIZED);
}