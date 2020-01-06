#include "Basket.h"
#include <algorithm>


Basket::Basket()
{
	this->sum = 0;
}


Basket::~Basket()
{
}

void Basket::addToBasket(Coat c)
{
	auto it = find_if(this->coats.begin(), this->coats.end(), [c](Coat &coat) {return c.getColour() == coat.getColour() && c.getSize() == coat.getSize(); });
	if (it == this->coats.end())
	{
		c.setQuantity(1);
		this->coats.push_back(c);
	}
	else
		(*it).increaseQuantity();
	this->sum += c.getPrice();
}