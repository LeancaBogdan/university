#pragma once
#include "Controller.h"

class UI
{
	Controller cont;

	/// <summary>
	/// Prints a given <see cref="Coat"/> instance.
	/// </summary>
	/// <param name="c">The <see cref="Coat"/> instance to be printed.</param>
	void printCoat(const Coat &c);

	/// <summary>
	/// Prints the admin menu.
	/// </summary>
	void printAdminMenu();

	void printUserMainMenu();

	/// <summary>
	/// Prints the user menu.
	/// </summary>
	void printUserMenu();

	/// <summary>
	/// The admin menu.
	/// </summary>
	void adminMenu();

	/// <summary>
	/// The user menu.
	/// </summary>
	void userMenu();

	/// <summary>
	/// The add menu.
	/// </summary>
	void addMenu();

	/// <summary>
	/// The remove menu.
	/// </summary>
	void removeMenu();

	/// <summary>
	/// The update menu.
	/// </summary>
	void updateMenu();

	/// <summary>
	/// Lists all the <see cref="Coat"> instances stored in the repository.
	/// </summary>
	void listAll();
	
	/// <summary>
	/// Lists all the <see cref="Coat"/> instances stored in the basket.
	/// </summary>
	void showBasket();

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="UI"/> class.
	/// </summary>
	/// <param name="cont">The <see cref="Controller"> instance associated to the newly created <see cref="UI"/> instance.</param>
	UI(Controller &cont);

	/// <summary>
	/// Finalizes an instance of the <see cref="UI"/> class.
	/// </summary>
	~UI();

	/// <summary>
	/// Starts the UI and gives the user the choice whether to run the application in Administrator or User mode.
	/// </summary>
	void modeChoice();
};