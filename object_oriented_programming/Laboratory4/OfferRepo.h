#pragma once
#include "Offer.h"
#define CAPACITY 10

typedef struct
{
	Offer **offers;
	int len;			//Actual length of the repository
	int capacity;		//Maximum capacity of the repository
} Offers;

/*
---------------------------------------------------------------
Creates a dynamically allocated repository of offers, with a given capacity
Input: capacity, integer representing the maximum capacity of the repository
Return: a pointer to the created repository
----------------------------------------------------------------
*/
Offers *createRepo(int capacity);

/*
-----------------------------------------------------------------
Destroys the dynamically allocated repository
Input: repo, a pointer to the repository to be destroyed
Return: -
-----------------------------------------------------------------
*/
void destroyRepo(Offers *repo);

/*
-----------------------------------------------------------------
Adds an offer to the repository
Input: repo, a pointer to the repository
	   o, a pointer to the offer to be added
Return: 1 - If the offer was successfully added to the repository
	    0 - If the offer could not be added to the repository
-----------------------------------------------------------------
*/
int addR(Offers *repo, Offer *o);

/*
-----------------------------------------------------------------
Deletes an offer from the repository by a given address
Input: repo, a pointer to the repository
	   address, a pointer to a string representing the address
Return: 1 - If the offer was successfully deleted from the repository
		0 - If the offer could not be removed from the repository
-----------------------------------------------------------------
*/
int deleteR(Offers *repo, char *address);

/*
--------------------------------------------------------------------
Updates an offer from the repository, by the address
Input: repo, a pointer to the repository
	   address, a pointer to a strinf representing the address
	   type, a pointer to a string representing the type
	   price, an integer representing the price
	   surface, an integer representing the surface
Return: 1 - If the offer was successfully updated
	    0 - If the offer could not be updated
*/
int updateR(Offers *repo, char *address, char *type, int price, int surface);

/*
-----------------------------------------------------------------
Returns the length of the repository
Input: repo, a pointer to the repository
Return: Integer representing the length of the repository
------------------------------------------------------------------
*/
int repoGetLength(Offers *repo);

/*
------------------------------------------------------------------
Returns the position in the repository of an offer with a given address
Input: repo, a pointer to the repository
	   address, a pointer to a string representing the address
Return: Integer representing the position
-------------------------------------------------------------------
*/
int getPos(Offers *repo, char *address);

/*
-------------------------------------------------------------------
Returns a pointer to the offer on a given position in the repository
Input: repo - a pointer to the repository
	   pos - integer representing the position
Return: a pointer to the offer
--------------------------------------------------------------------
*/
Offer *getOfferOnPos(Offers *repo, int pos);

//TESTS
void testsOffersRepo();