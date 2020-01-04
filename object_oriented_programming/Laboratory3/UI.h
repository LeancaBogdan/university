#pragma once
#include "Controller.h"
#include <stdio.h>

typedef struct
{
	Controller* cont;
} UI;

UI* createUI(Controller* c);
void destroyUI(UI* ui);

void startUI(UI* ui);
