#pragma once
#include "Controller.h"

class UI
{
	Controller *cont;

	void printAdminMenu();
	void printUserMenu();
	void adminMenu();
	void userMenu();
	void addMenu();
	void removeMenu();
	void updateMenu();
	void list();

public:
	///<summary>
	///Creates the UI
	///</summary>
	///<param cont> Pointer to the controller</param>
	UI(Controller *cont);

	///<summary>
	///Destroys the UI
	///</summary>
	~UI();

	///<summary>
	///Starts the UI and gives the user the choice to whether run the app in
	///Administrator mode, User mode or to exit
	///</summary>
	void modeChoice();
};

