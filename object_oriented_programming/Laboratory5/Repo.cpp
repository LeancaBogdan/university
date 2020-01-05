#include "Repo.h"


Repo::Repo()
{
}

Repo::~Repo()
{
}

Coat ** Repo::getList()
{
	Coat **c = this->coats.getAllElems();
	return c;
}

int Repo::getLength()
{
	return this->coats.getLength();
}

int Repo::getPos(std::string link)
{
	Coat **c = this->coats.getAllElems();
	for (int i = 0; i < this->coats.getLength(); i++)
		if (c[i]->getLink() == link)
			return i;
	return -1;
}

Coat * Repo::getCoatOnPos(int pos)
{
	if (pos < 0 || pos >= this->coats.getLength())
		return NULL;
	Coat **c = this->coats.getAllElems();
	return c[pos];
}

bool Repo::addR(Coat * c)
{
	if (this->getPos(c->getLink()) != -1)
		return false;
	this->coats = c + this->coats;
	return true;
}

bool Repo::removeR(std::string link)
{
	int pos = this->getPos(link);
	if (pos == -1)
		return false;
	this->coats.remove(pos);
	return true;
}

bool Repo::updateR(Coat * c)
{
	int pos = this->getPos(c->getLink());
	if (pos == -1)
		return false;
	this->coats.setElem(pos, c);
	return true;
}