#include "Repository.h"
#include <algorithm>
#include <fstream>

Repository::Repository()
{
}

Repository::Repository(std::string fileName)
	: fileName{ fileName }
{
	this->readFile();
}


Repository::~Repository()
{
}

void Repository::addToRepository(Coat & c)
{
	Coat c1{};
	try
	{
		c1 = this->getCoatBySizeAndColour(c.getSize(), c.getColour());
		throw DuplicateCoatException();
	}
	catch (InexistentCoatException) {}
	this->coats.push_back(c);
	this->writeFile();
	return;
}

void Repository::removeFromRepository(Coat & c)
{
	auto it = find(this->coats.begin(), this->coats.end(), c);
	if (it == this->coats.end())
		throw InexistentCoatException();
	this->coats.erase(it);
	this->writeFile();
	return;
}

void Repository::updateInRepository(Coat & c)
{
	Coat *c1{};
	c1 = this->getPointerToCoatBySizeAndColour(c.getSize(), c.getColour());
	if (c.getQuantity() == 0)
	{
		this->removeFromRepository(*c1);
		return;
	}
	c1->setPhoto(c.getPhoto());
	c1->setPrice(c.getPrice());
	c1->setQuantity(c.getQuantity());
	this->writeFile();
	return;
}

Coat *Repository::getPointerToCoatBySizeAndColour(const unsigned int & size, const std::string &colour)
{
	auto it = find_if(this->coats.begin(), this->coats.end(), [size, colour](Coat &c) {return c.getSize() == size && c.getColour() == colour; });
	if (it == this->coats.end())
		throw InexistentCoatException();
	return &(*it);
}

Coat Repository::getCoatBySizeAndColour(const unsigned int & size, const std::string &colour)
{
	for (auto coat : this->coats)
		if (coat.getColour() == colour && coat.getSize() == size)
			return coat;
	throw InexistentCoatException();
}

std::vector<Coat> Repository::filterRepoBySize(const unsigned int & size)
{
	std::vector<Coat> res{};
	for (auto coat : this->coats)
		if (coat.getSize() == size)
			res.push_back(coat);
	return res;
}


void Repository::readFile()
{
	std::ifstream file(this->fileName);

	if (!file.is_open())
		throw FileException("File can't be opened for read!");

	Coat c;
	while (file >> c)
		this->coats.push_back(c);
	file.close();
}

void Repository::writeFile()
{
	std::ofstream file(this->fileName);

	if (!file.is_open())
		throw FileException("File can't be opened for write!");

	for (auto coat : coats)
		file << coat;
	
	file.close();
	return;
}



RepositoryException::RepositoryException() : exception{}, message{ "" }
{
}

RepositoryException::RepositoryException(const std::string & msg) : message{ msg }
{
}

const char * RepositoryException::what()
{
	return this->message.c_str();
}

const char * DuplicateCoatException::what()
{
	return "There is another coat with the same size and colour!";
}

const char * InexistentCoatException::what()
{
	return "There are no coats with the given size and colour!";
}

FileException::FileException(const std::string & msg) : message(msg)
{
}

const char * FileException::what()
{
	return message.c_str();
}