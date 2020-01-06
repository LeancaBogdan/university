#include "Repository.h"
#include <algorithm>
#include <fstream>

Repository::Repository()
{
}

Repository::~Repository()
{
}

void Repository::addToRepository(Coat & c)
{
	this->coats.push_back(c);
}

void Repository::removeFromRepository(Coat & c)
{
	auto it = find(this->coats.begin(), this->coats.end(), c);
	if (it != this->coats.end())
	this->coats.erase(it);
}

void Repository::updateInRepository(Coat & c)
{
	Coat *c1{};
	c1 = this->getPointerToCoatBySizeAndColour(c.getSize(), c.getColour());
	if (c1 != nullptr)
	{
		if (c.getQuantity() == 0)
		{
			this->removeFromRepository(*c1);
			return;
		}
		c1->setPhoto(c.getPhoto());
		c1->setPrice(c.getPrice());
		c1->setQuantity(c.getQuantity());
	}
}

Coat* Repository::getPointerToCoatBySizeAndColour(const unsigned int & size, const std::string &colour)
{
	auto it = find_if(this->coats.begin(), this->coats.end(), [size, colour](Coat &c) {return c.getSize() == size && c.getColour() == colour; });
	if (it != this->coats.end())
		return &(*it);
	return nullptr;
}

Coat Repository::getCoatBySizeAndColour(const unsigned int & size, const std::string &colour)
{
	for (auto coat : this->coats)
		if (coat.getColour() == colour && coat.getSize() == size)
			return coat;
	return Coat();
}

std::vector<Coat> Repository::filterRepoBySize(const unsigned int & size)
{
	std::vector<Coat> res{};
	for (auto coat : this->coats)
		if (coat.getSize() == size)
			res.push_back(coat);
	return res;
}
