#include "Controller.h"



Controller::Controller(Repo *repo)
{
	this->repo = repo;
}


Controller::~Controller()
{
	delete this->repo;
}

bool Controller::addC(int size, std::string color, int price, int quant, std::string link)
{
	Coat * c = new Coat(size, color, price, quant, link);
	if (c == 0)
		return false;
	return this->repo->addR(c);
}

bool Controller::removeC(std::string link)
{
	return this->repo->removeR(link);
}

bool Controller::updateC(int size, std::string color, int price, int quant, std::string link)
{
	Coat * c = new Coat(size, color, price, quant, link);
	if (c == 0)
		return false;
	return this->repo->updateR(c);
}

Repo * Controller::getRepo()
{
	return this->repo;
}
