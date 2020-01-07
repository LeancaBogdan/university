#pragma once
#include "gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel.h>
#include <qpushbutton.h>
#include <qboxlayout.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	BasketCSV basket{};
	Repository repo{ "Repo.txt" };
	Controller cont{ repo , basket };
	GUI ui{ cont };

	ui.show();
	return a.exec();
}