#include "UI.h"
#include <iostream>
#include <crtdbg.h>

int Coat::coatCount = 0;

int mainc()
{
	Repo *repo = new Repo;
	Controller *cont = new Controller(repo);
	UI *ui = new UI(cont);

	Coat *c = new Coat(10, "Yellow", 100, 5, "fb.com");
	repo->addR(c);
	
	cont->addC(15, "Blue", 200, 10, "yt.com");
	cont->addC(7, "Marshmallow", 20, 100, "a.net");
	cont->addC(20, "Marine", 300, 5, "b.ro");
	cont->addC(25, "Gray", 750, 9, "d.net");
	cont->addC(28, "Black", 500, 100, "e.me");
	cont->addC(22, "White", 1000, 50, "white.net");
	cont->addC(25, "Leather", 175, 20, "leat.com");
	cont->addC(23, "Orange", 600, 1, "bau.com");
	cont->addC(27, "Metal", 400, 10, "rockfm.ro");
	
	ui->modeChoice();

	std::cout << Coat::coatCount << "\n";

	delete ui;
	
	system("pause");
	return 0;
}

int main()
{
	mainc();
	_CrtDumpMemoryLeaks();
	return 0;
}