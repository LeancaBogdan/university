#pragma once
#include "OfferRepo.h"
#include "OperationsStack.h"

typedef struct
{
	Offers *repo;
	OperationsStack *undoStack;
	OperationsStack *redoStack;

} Controller;

/*
------------------------------------------------------------
Creates a controller
Input: repo, a pointer to the repository
	   undoS, a pointer to the undo stack
Return: a pointer to the created controller
------------------------------------------------------------
*/
Controller *createController(Offers *repo, OperationsStack *undoS, OperationsStack *redoS);

/*
-------------------------------------------------------------
Destroys a controller
Input: cont, a pointer to the controller to be destroyed
Return: -
-------------------------------------------------------------
*/
void destroyController(Controller *cont);

/*
-------------------------------------------------------------
Adds an offer to the repository of offers
Input: cont, a pointer to the controller
	   address, a pointer to a string containing the address of the new offer
	   type, a pointer to a string containing the type of the new offer
	   surface, an integer representing the surface of the new offer
	   price, an integer representing the price of the new offer
Return: 1 - If the offer was successfully added
		0 - If the offer could not be added, as another offer with the same address is already stored.
-------------------------------------------------------------
*/
int addOffer(Controller *cont, char *address, char *type, int price, int surface);

/*
------------------------------------------------------------------------------------
Deletes an offer from the repository
Input: cont, a pointer to the controller
	   address, a pointer to a string containing the address
Return: 1 - If the offer was successfully added
		0 - If the offer could not be removed, as it does not exist
-------------------------------------------------------------------------------------
*/
int deleteOffer(Controller *cont, char *address);

/*
--------------------------------------------------------------------
Updates an offer from the repository, by the address
Input: cont, a pointer to the controller
	   address, a pointer to a strinf representing the address
	   type, a pointer to a string representing the type
	   price, an integer representing the price
	   surface, an integer representing the surface
Return: 1 - If the offer was successfully updated
		0 - If the offer could not be updated
*/
int updateOffer(Controller *cont, char *address, char *type, int price, int surface);

/*
----------------------------------------------------------------
Returns a pointer to the repository
Input: cont, a pointer to the controller
Return: a pointer to the repository
----------------------------------------------------------------
*/
Offers *getRepo(Controller *cont);

/*
----------------------------------------------------------------
Searches for the offers containing a certain string in the address attribute
Input: cont, a pointer to the controller
	   search, a pointer to the search string
Return: A pointer to a repository of offers that match the search string
-----------------------------------------------------------------
*/
Offers *filterByAddress(Controller *cont, char *search);

/*
----------------------------------------------------------------
Searches for the offers of a given type
Input: cont, a pointer to the controller
	   search, a pointer to the search string
Return: A pointer to a repository of offers that match the search string
-----------------------------------------------------------------
*/
Offers *filterByType(Controller *cont, char *search);

/*
-------------------------------------------------------------------
Sorts the entries in the given repository by address
Input: repo, a pointer to the repository to be sorted
-------------------------------------------------------------------
*/
void sortByAddress(Offers* repo);

/*
-------------------------------------------------------------------
Undoes the last performed operation
Input: cont, a pointer to the controller
Return: 1 - If the undo was performed
		0 - If there is no operation to undo
-------------------------------------------------------------------
*/
int undo(Controller *cont);

/*
-------------------------------------------------------------------
Redoes the last undone operation
Input: cont, a pointer to the controller
Return: 1 - If the undo was performed
		0 - If there is no operation to undo
-------------------------------------------------------------------
*/
int redo(Controller *cont);

//TESTS
void testsCont();