#include "Controller.h"



Controller::Controller()
{
}

Controller::~Controller()
{
}


void Controller::addController(const unsigned int & size, const std::string & colour, const unsigned int & price, const unsigned int & quantity, const std::string & photo)
{
	Coat c{ size, colour, price, quantity, photo };
	this->repo.addToRepository(c);
}

void Controller::removeController(const unsigned int & size, const std::string colour)
{
	Coat c = this->repo.getCoatBySizeAndColour(size, colour);
	this->repo.removeFromRepository(c);
}

void Controller::updateController(const unsigned int & size, const std::string & colour, const unsigned int & price, const unsigned int & quantity, const std::string & photo)
{
	Coat c{ size, colour, price, quantity, photo };
	this->repo.updateInRepository(c);
}

void Controller::addToBasket(Coat & c)
{
	this->basket.addToBasket(c);
}

