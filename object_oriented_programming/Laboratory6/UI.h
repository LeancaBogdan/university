#pragma once
#include "Controller.h"

class UI
{
	Controller *cont;

	void showBasket(int sum, Repo *basket);
	void printCoat(Coat *c);
	void printAdminMenu();
	void printUserMenu();
	void adminMenu();
	void userMenu();
	void addMenu();
	void removeMenu();
	void updateMenu();
	void list();

public:
	/// <summary>
	/// Initializes a new instance of the <see cref="UI"/> class.
	/// </summary>
	/// <param name="cont">Pointer to the controller.</param>
	UI(Controller *cont);

	/// <summary>
	/// Finalizes an instance of the <see cref="UI"/> class.
	/// </summary>
	~UI();

	/// <summary>
	/// Starts the UI and gives the user the choice whether to run the application in Administrator or User mode.
	/// </summary>
	void modeChoice();
};