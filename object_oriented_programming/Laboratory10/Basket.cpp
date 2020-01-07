#include "Basket.h"
#include <algorithm>
#include <fstream>
#include <Windows.h>
#include <shellapi.h>


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
	return;
}

BasketCSV::BasketCSV() : Basket()
{
	this->filename = "Basket.csv";
}

void BasketCSV::writeFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("Error opening file for write!");
	for (auto coat : this->coats)
		file << coat;
	file.close();
	return;
}

void BasketCSV::showBasket()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}

BasketHTML::BasketHTML() : Basket()
{
	this->filename = "Basket.html";
}

void BasketHTML::writeFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("Error opening file for write!");
	file << "<!DOCTYPE html> \n <html> \n \t<head> \n \t\t <title>Basket</title> \n";
	file << "\t</head> \n \t<body> \n \t\t<table border=\"1\"> \n \t\t<tr>\n";
	file << "\t\t\t<td>Size</td> \n \t\t\t<td>Color</td> \n \t\t\t<td>Price</td> \n \t\t\t <td>Quantity</td>\n";
	file << "\t\t\t<td>Link to photo</td> \n \t\t </tr>\n";
	for (auto coat : this->coats)
	{
		file << "\t\t<tr>\n";
		file << "\t\t\t<td>" << coat.getSize() << "</td>\n";
		file << "\t\t\t<td>" << coat.getColour() << "</td>\n";
		file << "\t\t\t<td>" << coat.getPrice() << "</td>\n";
		file << "\t\t\t<td>" << coat.getQuantity() << "</td>\n";
		file << "\t\t\t<td><a href=" << coat.getPhoto() << ">Link</td>\n";
		file << "\t\t</tr>\n";
	}
	file << "\t\t</table>\n";
	file << "\t</body>\n";
	file << "</html>\n";
	file.close();
}

void BasketHTML::showBasket()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}
