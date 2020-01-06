#pragma once
#include "Repo.h"
class Controller
{
	Repo *repo;
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Controller"/> class.
	/// </summary>
	/// <param name="repo">The repository.</param>
	Controller(Repo *repo);
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Controller"/> class.
	/// </summary>
	~Controller();
	
	/// <summary>
	/// Adds the coat given by its attributes to the repository.
	/// </summary>
	/// <param name="size">The size.</param>
	/// <param name="color">The color.</param>
	/// <param name="price">The price.</param>
	/// <param name="quant">The quant.</param>
	/// <param name="link">The link.</param>
	/// <returns>Boolean, True if successful, False otherwise</returns>
	bool addC(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link);
	
	/// <summary>
	/// Removes the coat given by its link from the repository.
	/// </summary>
	/// <param name="link">The link.</param>
	/// <returns>Boolean, True if successful, False otherwise</returns>
	bool removeC(std::string const &link);
	
	/// <summary>
	/// Updates the coat given by its link with the given attributes.
	/// </summary>
	/// <param name="size">The size.</param>
	/// <param name="color">The color.</param>
	/// <param name="price">The price.</param>
	/// <param name="quant">The quant.</param>
	/// <param name="link">The link.</param>
	/// <returns>Boolean, True if successful, False otherwise.</returns>
	bool updateC(int const &size, std::string const &color, int const &price, int const &quant, std::string const &link);
	
	/// <summary>
	/// Gets the repo.
	/// </summary>
	/// <returns>Pointer to the repository.</returns>
	Repo *getRepo();
	
	/// <summary>
	/// Filters the repository by a given size.
	/// </summary>
	/// <param name="size">The size.</param>
	/// <returns>Pointer to the filtered repository.</returns>
	Repo *filterBySize(unsigned int const &size);
};

