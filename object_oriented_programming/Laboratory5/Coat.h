#pragma once
//#include "DynamicVector.h"
#include <string>

class Coat
{
	int size;
	std::string color;
	int price;
	int quant;
	std::string link;

public:
	///<summary>
	///Constructor for the Coat objects
	///</summary>
	///<param size> Integer, the size of the coat</param>
	///<param color> String, the color of the coat</param>
	///<param price> Integer, the price of the coat</param>
	///<param quant> Integer, the quantity in the shop</param>
	///<param link> String, a link to the photo of the coat</param>
	///<returns> Nothing</returns>
	Coat(int size, std::string color, int price, int quant, std::string link);

	///<summary>
	///Destructor for the Coat objects
	///</summary>
	~Coat();

	///<summary>
	///Getter for the size of a Coat object
	///</summary>
	///<returns> An integer representing the size of the current Coat object</summary>
	int getSize();

	///<summary>
	///Getter for the color of a Coat object
	///</summary>
	///<returns> A string representing the color of the current Coat object</returns>
	std::string getColor();

	///<summary>
	///Getter for the price of a Coat object
	///</summary>
	///<returns> An integer representing the price of the current Coat object</returns>
	int getPrice();

	///<summary>
	///Getter for the quantity of a Coat object
	///</summary>
	///<returns> An integer representing the quantity of the current Coat object</returns>
	int getQuant();

	///<summary>
	///Getter for the link to the picture of a Coat object
	///</summary>
	///<returns> A string representing the link to the picture of the current Coat object</returns>
	std::string getLink();

	///<summary>
	///Setter for the size of a Coat object
	///</summary>
	///<param size> Integer, the new size for the Coat object</param>
	void setSize(int size);

	///<summary>
	///Setter for the color of a Coat object
	///</summary>
	///<param color> String, the new color of the Coat object</param>
	void setColor(std::string color);

	///<summary>
	///Setter for the price of a Coat object
	///</summary>
	///<param price> Integer, the new price of the Coat object</param>
	void setPrice(int price);

	///<summary>
	///Setter for the quantity of a Coat object
	///</summary>
	///<param quant> Integer, the new quantity of the Coat object</param>
	void setQuant(int quant);

	///<summary>
	///Setter for the link to the image of a Coat object
	///</summary>
	///<param link> String, the link to the new image of the Coat object</param>
	void setLink(std::string link);

	///<summary>
	///Override the equality comparison operator for Coat objects
	///</summary>
	///<param c2> The Coat object with which the current one will be compared</param>
	///<returns> True if the links of the two Coat objects are the same, False otherwise</returns>
	bool operator==(Coat c2);

	///<summary>
	///Override the "+" operator to be able to add a Coat to a DynamicVector
	///</summary>
	///<param v> The DynamicVector to which the new element will be added</param>
	//DynamicVector& operator+(DynamicVector v);
};

