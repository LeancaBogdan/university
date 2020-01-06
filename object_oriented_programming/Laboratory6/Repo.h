#pragma once
#include "Coat.h"
#include "DynamicVector.h"

class Repo
{
	DynamicVector<Coat*> *coats;
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Repo"/> class.
	/// </summary>
	Repo();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Repo"/> class.
	/// </summary>
	~Repo();
	
	/// <summary>
	/// Gets the list.
	/// </summary>
	/// <returns></returns>
	Coat **getList() const;
	
	/// <summary>
	/// Gets the length of the repository.
	/// </summary>
	/// <returns></returns>
	int getLength() const;
	
	/// <summary>
	/// Gets the position of the coat with the given link.
	/// </summary>
	/// <param name="link">The link.</param>
	/// <returns></returns>
	int getPos(std::string const &link) const;
	
	/// <summary>
	/// Gets the coat on position.
	/// </summary>
	/// <param name="pos">The position.</param>
	/// <returns></returns>
	Coat *getCoatOnPos(int const &pos) const;
	
	/// <summary>
	/// Adds the coat c to the repository.
	/// </summary>
	/// <param name="c">The c.</param>
	/// <returns></returns>
	bool addR(Coat *c);
	
	/// <summary>
	/// Removes the coat with the given link from the repository.
	/// </summary>
	/// <param name="link">The link.</param>
	/// <returns></returns>
	bool removeR(std::string const &link);
	
	/// <summary>
	/// Updates the coat c in the repository.
	/// </summary>
	/// <param name="c">The c.</param>
	/// <returns></returns>
	bool updateR(Coat * c);
};
