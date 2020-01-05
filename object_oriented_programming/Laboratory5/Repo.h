#pragma once
#include "Coat.h"
#include "DynamicVector.h"

class Repo
{
	DynamicVector coats;
public:
	///<summary>
	///Creates a dynamically allocated repository of Coat objects
	///</summary>
	///<param cap> Integer, the capacity of the newly created repository</param>
	Repo();

	///<summary>
	///Destroys a Repo instance
	///</summary>
	~Repo();

	///<summary>
	///Getter for the list of Coat objects in the current Repo object
	///</summary>
	///<returns> Pointer to a list of Coat objects</returns>
	Coat **getList();

	///<summary>
	///Getter for the length of the current Repo object
	///</summary>
	///<returns> Integer representing the length of the current Repo object</returns>
	int getLength();

	///<summary>
	///Searches for a Coat object in the repository by a link
	///</summary>
	///<param link> String, the link to a photo by which the Coat object is searched in the repository</param>
	///<returns> The position on which the Coat object with the given link is found in the repo, -1 if it doesn't exist in the repo</returns>
	int getPos(std::string link);

	///<summary>
	///Gets the Coat object on a given position
	///</summary>
	///<param pos> The position in the repo from which to get the Coat object</param>
	///<returns> Pointer to the Coat object if the position is valid, NULL otherwise</returns>
	Coat *getCoatOnPos(int pos);

	///<summary>
	///Adds a Coat object to the repository
	///</summary>
	///<param c> Pointer to the Coat object to be added to the repository</param>
	///<returns> True if the Coat object was successfully added to the repository, false otherwise</returns>
	bool addR(Coat *c);

	///<summary>
	///Removes a Coat object from the repository
	///</summary>
	///<param link> String, the link of the Coat object to be removed from the repository</param>
	///<returns> True if the Coat object was successfully removed from the repository, false otherwise</returns>
	bool removeR(std::string link);

	///<summary>
	///Updates a Coat object in the repository
	///</summary>
	///<param c> Pointer to the Coat object with the new attributes</param>
	///<returns> True if the Coat object was successfully updated, false otherwise
	bool updateR(Coat * c);
};
