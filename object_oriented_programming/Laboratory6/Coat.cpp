#include "Coat.h"
#include <Windows.h>
#include <shellapi.h>


Coat::Coat(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link)
{
	this->size = size;
	this->color = color;
	this->price = price;
	this->quant = quant;
	this->link = link;
	coatCount++;
}

Coat::Coat(Coat & c)
{
	this->size = c.size;
	this->color = c.color;
	this->price = c.price;
	this->quant = c.quant;
	this->link = c.link;
	coatCount++;
}

Coat& Coat::operator=(Coat &c)
{
	if (this == &c)
		return *this;
	this->size = c.size;
	this->color = c.color;
	this->price = c.price;
	this->quant = c.quant;
	this->link = c.link;
	coatCount++;
	return *this;
}

Coat::~Coat()
{
	coatCount--;
}

int Coat::getSize() const
{
	return this->size;
}

std::string Coat::getColor() const
{
	return this->color;
}

int Coat::getPrice() const
{
	return this->price;
}

int Coat::getQuant() const
{
	return this->quant;
}

std::string Coat::getLink() const
{
	return this->link;
}

void Coat::setSize(int const &size)
{
	this->size = size;
}

void Coat::setColor(std::string const &color)
{
	this->color = color;
}

void Coat::setPrice(int const &price)
{
	this->price = price;
}

void Coat::setQuant(int const &quant)
{
	this->quant = quant;
}

void Coat::setLink(std::string const &link)
{
	this->link = link;
}

bool Coat::operator==(Coat const &c2)
{
	if (this->link == c2.getLink())
		return true;
	return false;
}

void Coat::showPhoto()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL, SW_SHOWMAXIMIZED);
}

void Coat::decreaseQuant()
{
	this->quant--;
}

void Coat::increaseQuant()
{
	this->quant++;
}

int Coat::getCount()
{
	return coatCount;
}

