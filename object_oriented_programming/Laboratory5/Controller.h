#pragma once
#include "Repo.h"
class Controller
{
	Repo *repo;
public:
	///<summary>
	///Creates the controller
	///</summary>
	///<param repo> Pointer to the repository</param>
	Controller(Repo *repo);

	///<summary>
	///Destroys the controller
	///</summary>
	~Controller();

	///<summary>
	///Adds a coat to the repository
	///</summary>
	///<param size> Integer, the size of the coat to be added</param>
	///<param color> String, the color of the coat to be added</param>
	///<param price> Integer, the price of the coat to be added</param>
	///<param quant> Integer, the quantity in which the coat is available</param>
	///<param link> String, the link to the photo of the coat to be added</param>
	///<returns> True if the coat was successfully added, false otherwise</returns>
	bool addC(int size, std::string color, int price, int quant, std::string link);

	///<summary>
	///Removes a coat from the repository
	///</summary>
	///<param link> String, the link to the picture of the coat to be removed</param>
	///<returns> True if the coat was successfullt removed, false otherwise</returns>
	bool removeC(std::string link);

	///<summary>
	///Updates a coat in the repository
	///</summary>
	///<param size> Integer, the new size of the coat to be updated</param>
	///<param color> String, the new color of the coat to be updated</param>
	///<param price> Integer, the new price of the coat to be updated</param>
	///<param quant> Integer, the new quantity in which the coat is available</param>
	///<param link> String, the link to the photo of the coat to be added</param>
	///<returns> True if the coat was successfully updated, false otherwise</returns>
	bool updateC(int size, std::string color, int price, int quant, std::string link);

	///<summary>
	///Gets the repository
	///</summary>
	///<return> Pointer to the repository</return>
	Repo *getRepo();
};

