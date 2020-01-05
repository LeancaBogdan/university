#pragma once

typedef struct
{
	char address[100], type[11];
	int price, surface;
} Offer;

/*
------------------------------------------------------------------------
Allocates memmory for an Offer instance and writes it's attributes
Input: address, type, price and surface of the offer
Output: a pointer to the newly created instance
------------------------------------------------------------------------
*/
Offer* createOffer(char *address, char *type, int price, int surface);

/*
------------------------------------------------------------------------
Deallocates the memmory allocated for an Offer instance
Input: a pointer to the Offer instance to be destroyed
Output: -
------------------------------------------------------------------------
*/
void destroyOffer(Offer *o);

/*
------------------------------------------------------------------------
Creates a deep copy of an offer
Input: o, a pointer to the Offer instance to be copied
Return: a pointer to the copy
------------------------------------------------------------------------
*/
Offer *copyOffer(Offer *o);

/*
------------------------------------------------------------------------
Getter for the address of an Offer instance
Input: a pointer to the Offer instance to be used
Output: a string containing the address of the Offer instance
------------------------------------------------------------------------
*/
char *getAddress(Offer *o);

/*
------------------------------------------------------------------------
Getter for the type of an Offer instance
Input: a pointer to the Offer instance to be used
Output: a string containing the type of the Offer instance
------------------------------------------------------------------------
*/
char *getType(Offer *o);

/*
------------------------------------------------------------------------
Getter for the surface of an Offer instance
Input: a pointer to the Offer instance to be used
Output: an integer representing the surface of the Offer instance
------------------------------------------------------------------------
*/
int getSurface(Offer *o);

/*
------------------------------------------------------------------------
Getter for the price of an Offer instance
Input: a pointer to the Offer instance to be used
Output: an integer representing the price of the Offer instance
------------------------------------------------------------------------
*/
int getPrice(Offer *o);

/*
------------------------------------------------------------------------
Setter for the address of an Offer instance
Input: a pointer to the Offer instance to be used and the new address, as a string
Output: -
------------------------------------------------------------------------
*/
void setAddress(Offer *o, char *address);

/*
------------------------------------------------------------------------
Setter for the type of an Offer instance
Input: a pointer to the Offer instance to be used and the new type, as a string
Output: -
------------------------------------------------------------------------
*/
void setType(Offer *o, char *type);

/*
------------------------------------------------------------------------
Setter for the surface of an Offer instance
Input: a pointer to the Offer instance to be used and the new surface, as an integer
Output: -
------------------------------------------------------------------------
*/
void setSurface(Offer *o, int surface);

/*
------------------------------------------------------------------------
Setter for the price of an Offer instance
Input: a pointer to the Offer instance to be used and the new price, as an integer
Output: -
------------------------------------------------------------------------
*/
void setPrice(Offer *o, int price);

/*
-------------------------------------------------------------------------
Prints an offer as a string in a given string
Input: o - a pointer to the Offer instance to be printed
	   str - a pointer to a string where the given Offer instance will be printed
	   i - integer, representing the position of the offer in the repository
Return: -
--------------------------------------------------------------------------
*/
void toString(Offer *o, char *str, int i);