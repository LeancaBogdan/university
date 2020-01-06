#include "UI.h"
#include <iostream>
#include <sstream>

UI::UI(Controller * cont)
{
	this->cont = cont;
}

UI::~UI()
{
	delete this->cont;
}

void UI::modeChoice()
{
	while (true)
	{
		int option{ 0 };
		std::cout << "\nPlease choose a mode: \n";
		std::cout << "\t1. Administrator mode\n";
		std::cout << "\t2. User mode\n";
		std::cout << "\t0. Exit\n";
		do
		{
			std::cout << "Input a command: ";
			std::cin >> option;
		} while (option < 0 || option > 2);
		switch (option)
		{
		case 1:
		{
			this->adminMenu();
			break;
		}
		case 2:
		{
			this->userMenu();
			break;
		}
		case 0:
			return;
		}
	}
}

void UI::showBasket(int sum, Repo * basket)
{
	if (basket->getLength() == 0)
	{
		std::cout << "The basket is empty!\n";
		return;
	}
	for (int i = 0; i < basket->getLength(); i++)
		printCoat(basket->getCoatOnPos(i));
	std::cout << "TOTAL SUM: " << sum << "\n";
	return;
}

void UI::printCoat(Coat * c)
{
	std::string option{};
	std::cout << "Size: " << c->getSize() << "\n";
	std::cout << "Color: " << c->getColor() << "\n";
	std::cout << "Price: " << c->getPrice() << "\n";
	std::cout << "Quantity: " << c->getQuant() << "\n";
	std::cout << "Link to photo: " << c->getLink() << "\n\n";
	return;
}

void UI::printAdminMenu()
{
	std::cout << "Admin menu\n";
	std::cout << "\t1. Add a trench coat\n";
	std::cout << "\t2. Update a trench coat\n";
	std::cout << "\t3. Remove a trench coat\n";
	std::cout << "\t4. List all trench coats\n";
	std::cout << "\t0. Exit to the mode choice menu\n";
}

void UI::printUserMenu()
{
	std::cout << "Please give a size (none for all the trench coats) (integer only): ";
	return;
}

void UI::adminMenu()
{
	while (true)
	{
		this->printAdminMenu();
		int cmd{ 0 };
		do
		{
			std::cout << "Input your command: ";
			std::cin >> cmd;
		} while (cmd < 0 || cmd > 4);
		switch(cmd)
		{
		case 1:
		{
			this->addMenu();
			break;
		}
		case 2:
		{
			this->updateMenu();
			break;
		}
		case 3:
		{
			this->removeMenu();
			break;
		}
		case 4:
		{
			this->list();
			break;
		}
		case 0:
			return;
		}
	}
}

void UI::userMenu()
{
	unsigned int sum = 0;
	while (true)
	{
		unsigned int size{};
		std::string input{};
		std::cout << "User menu\n";
		std::cout << "Please input the size of the trench coat: "; std::cin >> input;
		std::stringstream str1(input);
		str1 >> size;
		if (!str1)
		{
			std::cerr << "You need to provide an integer!\n";
			return;
		}
		Repo *res = this->cont->filterBySize(size);
		if (res->getLength() == 0)
		{
			std::cout << "No coat with this size!";
			return;
		}
		Repo *basket = new Repo;
		int i = 0;
		while (i < res->getLength())
		{
			Coat *c = res->getCoatOnPos(i);
			std::cout << "Coat nr: " << i + 1 << "\n";
			this->printCoat(c);
			std::string option{};
			std::cout << "Open photo in browser?\n";
			std::cin >> option;
			while (option != "yes" && option != "no")
			{
				std::cout << "Invalid option!\n";
				std::cin >> option;
			}
			if (option == "yes")
				c->showPhoto();
			std::cout << "\n";

			std::cout << "Options: \n";
			std::cout << "\t1. Add the trench to the shopping basket\n";
			std::cout << "\t2. Next\n";
			std::cout << "\t3. Go to the basket\n";

			unsigned int cmd{};
			std::string input{};
			std::cout << "Please input the option: "; std::cin >> input;
			std::stringstream str1(input);
			str1 >> cmd;
			if (!str1)
			{
				std::cerr << "You need to provide an integer!\n";
				return;
			}
			
			if (cmd == 1)
			{
				if (basket->getPos(c->getLink()) == -1)
				{
					Coat *cc = new Coat(*c);
					cc->setQuant(1);
					basket->addR(cc);
				}
				else
					basket->getCoatOnPos(basket->getPos(c->getLink()))->increaseQuant();
				sum += c->getPrice();
				c->decreaseQuant();
				if (c->getQuant() == 0)
				{
					this->cont->removeC(c->getLink());
					res->removeR(c->getLink());
				}
				continue;
			}
			else if (cmd == 2)
			{
				if (i == res->getLength())
					i = -1;
				continue;
			}
			else if (cmd == 3)
			{
				this->showBasket(sum, basket);
				delete basket;
				delete res;
				return;
			}
			i++;
		}
		//delete res;
	}
}

void UI::addMenu()
{
	std::string color{}, link{}, input{};
	int size{}, price{}, quant{};
	std::cout << "Please input the size of the trench coat: "; std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	if (!str1)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the color of the trench coat: "; std::cin >> color;
	std::cout << "Please input the price of the trench coat: "; std::cin >> input;
	std::stringstream str2(input);
	str2 >> price;
	if (!str2)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the quantity of the trench coat: "; std::cin >> input;
	std::stringstream str3(input);
	str3 >> quant;
	if (!str1)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input a link to a photo of the trench coat: "; std::cin >> link;
	if (quant == 0)
	{
		std::cerr << "Quantity cannot be 0!";
		return;
	}
	bool res = this->cont->addC(size, color, price, quant, link);
	if (res)
		std::cout << "Add successfull!\n";
	else
		std::cout << "Error! Trench coat with the same picture already stored!\n";
	return;
}

void UI::removeMenu()
{
	std::string link{};
	std::cout << "Please input the link to the photo of the trench coat to be removed: ";
	std::cin >> link;
	bool res = this->cont->removeC(link);
	if (res)
		std::cout << "Remove successfull!\n";
	else
		std::cout << "Error! No trench coat with the given link stored!\n";
	return;
}

void UI::updateMenu()
{
	std::string color{}, link{}, input{};
	int size{}, price{}, quant{};
	std::cout << "Please input a link to a photo of the trench coat to be updated: "; std::cin >> link;
	std::cout << "Please input the new size of the trench coat (integer only): "; std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	if (!str1)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the new color of the trench coat: "; std::cin >> color;
	std::cout << "Please input the new price of the trench coat (integer only): "; std::cin >> input;
	std::stringstream str2(input);
	str2 >> price;
	if (!str2)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the new quantity of the trench coat (integer only): "; std::cin >> input;
	std::stringstream str3(input);
	str3 >> quant;
	if (!str3)
	{
		std::cerr << "You need to provide an integer!\n";
		return;
	}
	if (quant == 0)
	{
		bool res = this->cont->removeC(link);
		if (res)
			std::cout << "Remove successfull!\n";
		else
			std::cout << "Error! No trench coat with the given picture stored!\n";
		return;
	}
	bool res = this->cont->updateC(size, color, price, quant, link);
	if (res)
		std::cout << "Update successfull!\n";
	else
		std::cout << "Error! No trench coat with the given picture stored!\n";
	return;
}

void UI::list()
{
	Repo *repo = this->cont->getRepo();
	if (repo->getLength() == 0)
	{
		std::cout << "No trench coat stored!\n";
		return;
	}
	for (int i = 0; i < repo->getLength(); i++)
	{
		Coat *c = repo->getCoatOnPos(i);
		std::cout << "Coat nr. " << i+1 << ": \n";
		std::cout << "Size: " << c->getSize() << "\n";
		std::cout << "Color: " << c->getColor() << "\n";
		std::cout << "Price: " << c->getPrice() << "\n";
		std::cout << "Quantity: " << c->getQuant() << "\n";
		std::cout << "Link to photo: " << c->getLink() << "\n\n";
	}
	return;
}
