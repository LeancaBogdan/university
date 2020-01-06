#include "Controller.h"



Controller::Controller(Repo *repo)
{
	this->repo = repo;
}


Controller::~Controller()
{
	delete this->repo;
}

bool Controller::addC(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link)
{
	Coat * c = new Coat(size, color, price, quant, link);
	if (c == 0)
		return false;
	return this->repo->addR(c);
}

bool Controller::removeC(std::string const &link)
{
	return this->repo->removeR(link);
}

bool Controller::updateC(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link)
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

Repo * Controller::filterBySize(unsigned int const & size)
{
	Repo *res = new Repo;
	for (int i = 0; i < this->repo->getLength(); i++)
		if (this->getRepo()->getCoatOnPos(i)->getSize() == size)
		{
			Coat *cc = new Coat(*(this->getRepo()->getCoatOnPos(i)));
			res->addR(cc);
		}
	return res;
}
