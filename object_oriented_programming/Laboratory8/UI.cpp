#include "UI.h"
#include <iostream>
#include <sstream>

UI::UI(Controller & cont) : cont{ cont }
{
}

UI::~UI()
{
}

void UI::modeChoice()
{
	while (true)
	{
		system("CLS");
		int option{ 0 };
		std::cout << "Please choose a mode: \n";
		std::cout << "\t1. Administrator mode\n";
		std::cout << "\t2. User mode\n";
		std::cout << "\t0. Exit\n";
		std::cout << "Please enter choice: ";
		std::cin >> option;
		while (option < 0 && option > 2)
		{
			std::cout << "Invalid option! :(\n Try again: ";
			std::cin >> option;
		}
		switch (option)
		{
		case 1:
		{
			this->adminMenu();
			system("CLS");
			break;
		}
		case 2:
		{
			this->userMenu();
			system("CLS");
			break;
		}
		case 0:
			return;
		}
	}
}

void UI::printCoat(const Coat & c)
{
	std::cout << "Size: " << c.getSize() << ", ";
	std::cout << "Color: " << c.getColour() << ", ";
	std::cout << "Price: " << c.getPrice() << ", ";
	std::cout << "Quantity: " << c.getQuantity() << ", ";
	std::cout << "Link to photo: " << c.getPhoto() << "\n";
}
#pragma region admin
void UI::printAdminMenu()
{
	system("CLS");
	std::cout << "Administration menu\n";
	std::cout << "\t1. Add a trench coat.\n";
	std::cout << "\t2. Update a trench coat.\n";
	std::cout << "\t3. Remove a trench coat.\n";
	std::cout << "\t4. List all trench coats.\n";
	std::cout << "\t0. Exit to the mode choice menu.\n";
}

void UI::adminMenu()
{
	while (true)
	{
		this->printAdminMenu();
		int option{ 0 };
		std::cout << "Please choose an option: ";
		std::cin >> option;
		while (option < 0 && option > 4)
		{
			std::cout << "Invalid option! :(\n Try again: ";
			std::cin >> option;
		}
		switch (option)
		{
		case 1:
		{
			this->addMenu();
			system("pause");
			break;
		}
		case 2:
		{
			this->updateMenu();
			system("pause");
			break;
		}
		case 3:
		{
			this->removeMenu();
			system("pause");
			break;
		}
		case 4:
		{
			this->listAll();
			system("pause");
			break;
		}
		case 0:
			return;
		}
	}
}

void UI::addMenu()
{
	std::string color{}, photo{}, input{};
	unsigned int size{}, price{}, quant{};
	std::cout << "Please input the size of the trench coat: "; std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	if (!str1)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the color of the trench coat: "; std::cin >> color;
	std::cout << "Please input the price of the trench coat: "; std::cin >> input;
	std::stringstream str2(input);
	str2 >> price;
	if (!str2)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the quantity of the trench coat: "; std::cin >> input;
	std::stringstream str3(input);
	str3 >> quant;
	if (!str1)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input a link to a photo of the trench coat: "; std::cin >> photo;
	if (quant == 0)
	{
		std::cout << "Quantity cannot be 0!";
		return;
	}
	try
	{
		this->cont.addController(size, color, price, quant, photo);
		std::cout << "Add successful! :)\n";
	}
	catch (DuplicateCoatException &e)
	{
		std::cout << e.what();
	}
}

void UI::removeMenu()
{
	std::string input{}, colour{};
	unsigned int size{};
	std::cout << "Please input the size of the trench coat: "; std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	if (!str1)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the colour of the trench coat: ";
	std::cin >> colour;
	try
	{
		this->cont.removeController(size, colour);
		std::cout << "Remove successful! :)\n";
	}
	catch (InexistentCoatException &e)
	{
		std::cout << e.what();
	}
}

void UI::updateMenu()
{
	std::string colour{}, photo{}, input{};
	unsigned int size{}, price{}, quant{};
	std::cout << "Please input the size of the trench coat to be updated (integer only): "; std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	if (!str1)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the colour of the trench coat to be updated: "; std::cin >> colour;
	std::cout << "Please input the new price of the trench coat (integer only): "; std::cin >> input;
	std::stringstream str2(input);
	str2 >> price;
	if (!str2)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	std::cout << "Please input the new quantity of the trench coat (integer only): "; std::cin >> input;
	std::stringstream str3(input);
	str3 >> quant;
	if (!str3)
	{
		std::cout << "You need to provide an integer!\n";
		return;
	}
	if (quant == 0)
	{
		try
		{
			this->cont.removeController(size, colour);
			std::cout << "Remove successful! :)\n";
		}
		catch (InexistentCoatException &e)
		{
			std::cout << e.what();
		}
	}
	std::cout << "Please input the new link to thw photo of the trench coat: ";
	std::cin >> photo;
	try
	{
		this->cont.updateController(size, colour, price, quant, photo);
	}
	catch (InexistentCoatException &e)
	{
		std::cout << e.what();
	}
}

void UI::listAll()
{
	std::vector<Coat> res = this->cont.getListInController();
	if (res.size() == 0)
	{
		std::cout << "No trench coat stored!\n";
		return;
	}
	for (auto coat : res)
		this->printCoat(coat);
	return;
}
#pragma endregion

#pragma region user
void UI::printUserMenu()
{
	std::cout << "Options: \n";
	std::cout << "\t1. Add the trench to the shopping basket.\n";
	std::cout << "\t2. Next.\n";
	std::cout << "\t3. Go to the basket.\n";
}

void UI::userMenu()
{
	system("CLS");
	std::cout << "Please give the size of the trench coats to be shown (integer only) ('all' for all the trench coats): ";
	std::string input{};
	unsigned int size{};
	std::vector<Coat> res{};
	std::cin >> input;
	std::stringstream str1(input);
	str1 >> size;
	while (!str1 && input != "all")
	{
		std::cout << "You need to provide an integer or 'all'! \n Try again: ";
		std::cin >> input;
		std::stringstream str1(input);
		str1 >> size;
	}
	if (input == "all")
		res = this->cont.getListInController();
	else
	{
		res = this->cont.filterRepoBySize(size);
	}

	if (res.size() == 0)
	{
		std::cout << "No trench coat with the given size is stored! :(\n";
		return;
	}
	unsigned int i = 0;
	while (i < res.size())
	{
		this->printCoat(res[i]);
		std::string option1{};
		std::cout << "Open photo in browser (yes or no)?\n";
		std::cin >> option1;
		while (option1 != "yes" && option1 != "no")
		{
			std::cout << "Invalid option! :(\n Try again: ";
			std::cin >> option1;
		}
		if (option1 == "yes")
			res[i].showPhoto();

		this->printUserMenu();
		int option{};
		std::string input{};
		std::cout << "Please choose an option: ";
		std::cin >> input;
		std::stringstream str1(input);
		str1 >> option;
		if (!str1)
		{
			std::cout << "You need to provide an integer! \n Try again: ";
			std::cin >> input;
			std::stringstream str1(input);
			str1 >> option;
		}
		if (option == 1)
		{
			this->cont.addToBasket(res[i]);
			if (res[i].getQuantity() == 1)
			{
				this->cont.removeController(res[i].getSize(), res[i].getColour());
				res.erase(res.begin() + i);
			}
			else
			{
				this->cont.updateController(res[i].getSize(), res[i].getColour(), res[i].getPrice(), res[i].getQuantity() - 1, res[i].getPhoto());
				res[i].decreaseQuantity();
			}
			std::cout << "Coat successfully added to the basket! :)\n";
			continue;
		}

		else if (option == 2)
		{
			if (i == res.size() - 1)
				i = -1;
			continue;
		}
		else if (option == 3)
		{
			this->showBasket();
			system("pause");
			return;
		}
		i++;
	}
}

void UI::showBasket()
{
	for (auto coat : this->cont.getListInBasket())
		this->printCoat(coat);
	std::cout << "TOTAL SUM: " << this->cont.getSumInBasket() << "\n";
	return;
}
#pragma endregion