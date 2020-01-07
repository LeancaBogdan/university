#ifndef GUI_H
#define GUI_H

#include "Controller.h"
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qwidget.h>

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(Controller &c, QWidget *parent = 0);
	~GUI();

private:
	Controller &cont;
	std::vector<Coat> currentCoatsInRepoList;

	QListWidget *repoList;
	QLineEdit *sizeEdit;
	QLineEdit *colourEdit;
	QLineEdit *priceEdit;
	QLineEdit *quantityEdit;
	QLineEdit *photoEdit;
	QPushButton *addButton;
	QPushButton *removeButton;
	QPushButton *updateButton;
	QPushButton *moveOneCoatButton;
	QPushButton *moveAllCoatsButton;
	QListWidget *basket;

	void initGUI();
	void populateRepoList();
	//void populateBasket();
	//int getRepoListSelectedIndex();
};

#endif // GUI_H
