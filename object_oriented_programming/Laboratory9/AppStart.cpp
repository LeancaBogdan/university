#pragma once
#include "UI.h"
#include <iostream>
#include "Tests.h"


int main()
{
	std::string filename{};
	std::cout << "Please give the filename for the repository: ";
	std::cin >> filename;

	system("CLS");
	
	std::string input{};
	unsigned int option;
	std::cout << "Types of basket: \n";
	std::cout << "\t1. CSV file.\n";
	std::cout << "\t2. HTML file.\n";
	std::cout << "Please input your option: ";
	std::cin >> option;
	Basket *basket = nullptr;
	if (option == 1)
	{
		basket = new BasketCSV{};
	}
	else if (option == 2)
		basket = new BasketHTML{};

	Repository repo{ filename };
	Controller cont{ repo , basket};
	UI ui{ cont };
	
	ui.modeChoice();

	system("pause");
	return 0;
}


//int main()
//{
//	Tests test;
//	test.testAll();
//	return 0;
//}