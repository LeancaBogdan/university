#pragma once
#include "Repository.h"
#include "Basket.h"

class Controller
{
	Repository repo;
	BasketCSV basket;

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Controller"/> class.
	/// </summary>
	Controller();

	/// <summary>
	/// Initializes a new instance of the <see cref="Controller"/> class.
	/// </summary>
	/// <param name="re">The repository to be associated with the current <see cref="Controller"/> instance.</param>
	Controller(Repository &re, BasketCSV &basket) : repo{ re }, basket{ basket } {}

	/// <summary>
	/// Finalizes an instance of the <see cref="Controller"/> class.
	/// </summary>
	~Controller();

	/// <summary>
	/// Adds a <see cref="Coat" /> instance to the repository.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <param name="colour">std::string, the colour.</param>
	/// <param name="price">Unsigned integer, the price.</param>
	/// <param name="quantity">Unsigned integer, the quantity.</param>
	/// <param name="photo">std::string, the photo.</param>
	/// <throws>DuplicateCoatException</throws>
	void addController(const unsigned int &size, const std::string &colour, const unsigned int &price, const unsigned int &quantity, const std::string &photo);

	/// <summary>
	/// Removes a <see cref="Coat"/> instance from the repository by size and colour.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <param name="colour">std::string, the colour.</param>
	/// <throws>InexistentCoatException</throws>
	void removeController(const unsigned int &size, const std::string colour);

	/// <summary>
	/// Updates a <see cref="Coat"/> instance in the repository identified by size and colour.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <param name="colour">std::string, the colour.</param>
	/// <param name="price">Unsigned integer, the price.</param>
	/// <param name="quantity">Unsigned integer, the quantity.</param>
	/// <param name="photo">std::string, the photo.</param>
	/// <throws>InexistentCoatException</throws>
	void updateController(const unsigned int &size, const std::string &colour, const unsigned int &price, const unsigned int &quantity, const std::string &photo);

	/// <summary>
	/// Gets the list of <see cref="Coat"/> instances stored in the repository.
	/// </summary>
	/// <returns>std::vector of <see cref="Coat"/> instances.</returns>
	const std::vector<Coat> &getListInController() { return this->repo.getListInRepository(); }

	/// <summary>
	/// Filters the repository by size.
	/// </summary>
	/// <param name="size">Unsigned integer, the size.</param>
	/// <returns>std::vector of <see cref="Coat"/> instances having the given size.</returns>
	std::vector<Coat> filterRepoBySize(const unsigned int &size) { return this->repo.filterRepoBySize(size); }

	/// <summary>
	/// Adds a <see cref="Coat"/> instance to the basket.
	/// </summary>
	/// <param name="c"><see cref="Coat"/>, the instance to be added to the basket.</param>
	void addToBasket(Coat &c);

	/// <summary>
	/// Gets the list of <see cref="Coat"/> instances stored in the basket.
	/// </summary>
	/// <returns>std::vector of <see cref="Coat"/> instances.</returns>
	const std::vector<Coat> &getListInBasket() { return this->basket.getListInBasket(); }

	/// <summary>
	/// Gets the sum in the basket.
	/// </summary>
	/// <returns>Unsigned integer, the sum in the basket.</returns>
	const unsigned int &getSumInBasket() { return this->basket.getSum(); }

	void showBasket() { this->basket.showBasket(); }

	void writeBasket() { this->basket.writeFile(); }
};

