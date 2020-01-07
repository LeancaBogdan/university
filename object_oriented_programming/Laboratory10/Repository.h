#pragma once
#include "Coat.h"
#include <vector>

class Repository
{
	std::vector<Coat> coats;
	std::string fileName;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Repository"/> class.
	/// </summary>
	Repository();
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Repository"/> class.
	/// </summary>
	/// <param name="fileName">Name of the file.</param>
	Repository(std::string fileName);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Repository"/> class.
	/// </summary>
	~Repository();
	
	/// <summary>
	/// Adds a <see cref="Coat"/> instance to the repository.
	/// </summary>
	/// <param name="c"><see cref="Coat"/>, the instance to be added.</param>
	/// <throws>DuplicateCoatException</throws>
	void addToRepository(Coat &c);
	
	/// <summary>
	/// Removes a <see cref="Coat"/> instance from the repository identified by size and colour.
	/// </summary>
	/// <param name="c"><see cref="Coat"/>, an instance with the desired size and colour for the remvove.</param>
	/// <throws>InexistentCoatException</throws>
	void removeFromRepository(Coat &c);
	
	/// <summary>
	/// Updates a <see cref="Coat"/> instance in the repository identified by size and colour.
	/// </summary>
	/// <param name="c"><see cref="Coat"/>, the instance with the updated fields.</param>
	/// <throws>InexistentCoatException</throws>
	void updateInRepository(Coat &c);
	
	/// <summary>
	/// Gets the length of the repository.
	/// </summary>
	/// <returns>Unsigned integer, the length of the repository.</returns>
	unsigned int getRepositoryLength() const { return this->coats.size(); }
	
	/// <summary>
	/// Gets a <see cref="Coat"/> instance by size and colour.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <param name="colour">std::string, the colour.</param>
	/// <returns>The <see cref="Coat"/> instance with the given size and colour</returns>
	/// <throws>InexistentCoatException</throws>
	Coat getCoatBySizeAndColour(const unsigned int &size, const std::string &colour);
	
	/// <summary>
	/// Gets a pointer to a <see cref="Coat"/> instance by size and colour.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <param name="colour">std::string, the colour.</param>
	/// <returns>A pointer to the <see cref="Coat"/> instance by size and colour.</returns>
	/// <throws>InexistentCoatException</throws>
	Coat *Repository::getPointerToCoatBySizeAndColour(const unsigned int & size, const std::string &colour);
		
	/// <summary>
	/// Gets the list in the repository.
	/// </summary>
	/// <returns>std::vector of all the <see cref="Coat"/> instances stored in the repository.</returns>
	const std::vector<Coat> &getListInRepository() { return this->coats; }
	
	/// <summary>
	/// Filters the repository by size.
	/// </summary>
	/// <param name="size">Unsigend integer, the size.</param>
	/// <returns>std::vector of all the <see cref="Coat"/> instances with the given size stored in the repository.</returns>
	std::vector<Coat> filterRepoBySize(const unsigned int &size);
		
	/// <summary>
	/// Reads the repository from the file.
	/// </summary>
	/// <throws>FileException</throws>
	void readFile();
	
	/// <summary>
	/// Writes the repository to the file.
	/// </summary>
	/// <throws>FileException</throws>
	void writeFile();
};

class RepositoryException : public std::exception
{
protected:
	std::string message;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="RepositoryException"/> class.
	/// </summary>
	RepositoryException();
		
	/// <summary>
	/// Initializes a new instance of the <see cref="RepositoryException"/> class.
	/// </summary>
	/// <param name="msg">The MSG.</param>
	RepositoryException(const std::string& msg);
		
	/// <summary>
	/// Finalizes an instance of the <see cref="RepositoryException"/> class.
	/// </summary>
	virtual ~RepositoryException() {}
		
	/// <summary>
	/// Gets the message associated with the current <see cref="RepositoryException"/> instance.
	/// </summary>
	/// <returns>Pointer to an array of chars containing the message associated with the current <see cref="RepositoryException"/> instance.</returns>
	virtual const char* what();
};

class DuplicateCoatException : public RepositoryException
{
public:
	const char* what();
};

class InexistentCoatException : public RepositoryException
{
public:
	const char* what();
};

class FileException : public std::exception
{
protected:
	std::string message;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="FileException"/> class.
	/// </summary>
	/// <param name="msg">The MSG.</param>
	FileException(const std::string& msg);
	
	/// <summary>
	/// Gets the message associated with the current <see cref="FileException"/> instance.
	/// </summary>
	/// <returns>Pointer to an array of chars containing the message associated with the current <see cref="FileException"/> instance.</returns>
	virtual const char* what();
};