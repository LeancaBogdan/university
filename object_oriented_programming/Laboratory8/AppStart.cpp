#pragma once
#include "UI.h"
#include <iostream>
#include "Tests.h"


//int main()
//{
//	Repository repo{};
//	Controller cont{ repo };
//	UI ui{ cont };
//	
//	ui.modeChoice();
//
//	system("pause");
//	return 0;
//}



int main()
{
	Tests test;
	test.testAll();
	return 0;
}
