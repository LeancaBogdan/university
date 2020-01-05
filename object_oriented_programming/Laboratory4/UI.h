#pragma once
#include "Controller.h"

typedef struct
{
	Controller *cont;
} UI;

/*
---------------------------------------------------------
Creates the UI
Input: cont - a pointer to the controller
Return: a pointer to the UI
----------------------------------------------------------
*/
UI *createUI(Controller *cont);

/*
----------------------------------------------------------
Destroys the UI
Input: ui - a pointer to the UI to be destroyed
Return: -
----------------------------------------------------------
*/
void destroyUI(UI *ui);

/*
-----------------------------------------------------------
Starts the UI
Input: ui - a pointer to the UI
Return: -
-----------------------------------------------------------
*/
void startUI(UI *ui);