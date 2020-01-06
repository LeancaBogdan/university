#include "Repo.h"


Repo::Repo()
{
	this->coats = new DynamicVector<Coat*>(10);
}

Repo::~Repo()
{
	for (int i = 0; i < this->getLength(); i++)
		delete this->getCoatOnPos(i);
	delete this->coats;
}

Coat ** Repo::getList() const
{
	Coat **c = this->coats->getAllElems();
	return c;
}

int Repo::getLength() const
{
	return this->coats->getLength();
}

int Repo::getPos(std::string const &link) const
{
	Coat **c = this->coats->getAllElems();
	for (int i = 0; i < this->coats->getLength(); i++)
		if (c[i]->getLink() == link)
			return i;
	return -1;
}

Coat * Repo::getCoatOnPos(int const &pos) const
{
	if (pos < 0 || pos >= this->coats->getLength())
		return NULL;
	Coat **c = this->coats->getAllElems();
	return c[pos];
}

bool Repo::addR(Coat *c) 
{
	if (this->getPos(c->getLink()) != -1)
		return false;
	this->coats->add(c);
	return true;
}

bool Repo::removeR(std::string const &link)
{
	int pos = this->getPos(link);
	if (pos == -1)
		return false;
	this->coats->remove(pos);
	return true;
}

bool Repo::updateR(Coat * c)
{
	int pos = this->getPos(c->getLink());
	if (pos == -1)
		return false;
	this->coats->setElem(pos, c);
	return true;
}