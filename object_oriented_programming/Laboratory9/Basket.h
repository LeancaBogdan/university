#pragma once
#include "Coat.h"
#include <vector>
#include "Repository.h"

class Basket
{
protected:
	std::vector<Coat> coats;
	unsigned int sum;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Basket"/> class.
	/// </summary>
	Basket();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Basket"/> class.
	/// </summary>
	~Basket();
	
	/// <summary>
	/// Adds a <see cref="Coat"/> instance to basket.
	/// </summary>
	/// <param name="c">The <see cref="Coat"/> instance to be added.</param>
	void addToBasket(Coat c);
	
	/// <summary>
	/// Gets the list in the current <see cref="Basket"/> instance.
	/// </summary>
	/// <returns>A std::vector of <see cref="Coat"/> instances.</returns>
	const std::vector<Coat> &getListInBasket() { return this->coats; }
	
	/// <summary>
	/// Gets the sum in the current <see cref="Basket"/> instance.
	/// </summary>
	/// <returns>Unsigned int, the sum in the current <see cref="Basket"/> instance.</returns>
	const unsigned int &getSum() { return this->sum; }

	virtual void showBasket() = 0;

	virtual void writeFile() = 0;
};

class BasketCSV : public Basket
{
	std::string filename;

public:
	BasketCSV();
	void writeFile() override;
	void showBasket() override;
};

class BasketHTML : public Basket
{
	std::string filename;

public:
	BasketHTML();
	void writeFile() override;
	void showBasket() override;
};