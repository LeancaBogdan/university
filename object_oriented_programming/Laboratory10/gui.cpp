#include "gui.h"
#include <qmessagebox.h>
#include <qwidget.h>

GUI::GUI(Controller &c, QWidget *parent) : cont{ c }, QWidget{ parent }
{
	this->initGUI();
	this->currentCoatsInRepoList = this->cont.getListInController();
	this->populateRepoList();
}

GUI::~GUI()
{

}

void GUI::initGUI()
{
	QHBoxLayout *layout = new QHBoxLayout{ this };

	QWidget *leftWidget = new QWidget{};
	QVBoxLayout *leftSide = new QVBoxLayout{ leftWidget };

	this->repoList = new QListWidget{};
	this->repoList->setSelectionMode(QAbstractItemView::SingleSelection);

	QWidget *coatDataWidget = new QWidget{};
	QFormLayout *formLayout = new QFormLayout{ coatDataWidget };
	this->sizeEdit = new QLineEdit{};
	this->colourEdit = new QLineEdit{};
	this->priceEdit = new QLineEdit{};
	this->quantityEdit = new QLineEdit{};
	this->photoEdit = new QLineEdit{};
	formLayout->addRow("&Size:", sizeEdit);
	formLayout->addRow("&Colour:", colourEdit);
	formLayout->addRow("&Price:", priceEdit);
	formLayout->addRow("&Quantity:", quantityEdit);
	formLayout->addRow("&Photo: ", photoEdit);

	QWidget *buttonsWidget = new QWidget{};
	QGridLayout *gridLayout = new QGridLayout{ buttonsWidget };
	this->addButton = new QPushButton{ "Add" };
	this->removeButton = new QPushButton{ "Remove" };
	this->updateButton = new QPushButton{ "Update" };

	gridLayout->addWidget(addButton, 0, 0);
	gridLayout->addWidget(removeButton, 0, 1);
	gridLayout->addWidget(updateButton, 0, 2);

	leftSide->addWidget(new QLabel{ "All coats" });
	leftSide->addWidget(repoList);
	leftSide->addWidget(coatDataWidget);
	leftSide->addWidget(buttonsWidget);

	QWidget *middleWidget = new QWidget{};
	QVBoxLayout *vLayoutMiddle = new QVBoxLayout{ middleWidget };
	this->moveOneCoatButton = new QPushButton{ ">> Move one coat" };
	this->moveAllCoatsButton = new QPushButton{ ">> Move all coats with selected type" };
	QWidget *upperPart = new QWidget{};
	QWidget *lowerPart = new QWidget{};
	QVBoxLayout *vLayoutUpperPart = new QVBoxLayout{ upperPart };
	vLayoutUpperPart->addWidget(this->moveOneCoatButton);
	vLayoutUpperPart->addWidget(this->moveAllCoatsButton);
	vLayoutMiddle->addWidget(upperPart);
	vLayoutMiddle->addWidget(lowerPart);

	QWidget *rightWidget = new QWidget{};
	QVBoxLayout *rightLayout = new QVBoxLayout{ rightWidget };

	this->basket = new QListWidget{};

	QWidget *basketWidget = new QWidget{};
	QHBoxLayout *basketLayout = new QHBoxLayout{ basketWidget };
	basketLayout->addWidget(new QPushButton{ "&Show photo" });
	basketLayout->addWidget(new QPushButton{ "&Remove" });

	rightLayout->addWidget(new QLabel{ "Basket" });
	rightLayout->addWidget(this->basket);
	rightLayout->addWidget(basketWidget);

	layout->addWidget(leftWidget);
	layout->addWidget(middleWidget);
	layout->addWidget(rightWidget);
}

void GUI::populateRepoList()
{
	if (this->repoList->count() > 0)
		this->repoList->clear();

	for (auto c : this->currentCoatsInRepoList)
	{
		QString itemInList = QString::fromStdString(std::to_string(c.getSize()) + " - " + c.getColour() + " - " + std::to_string(c.getPrice()) + " - " + std::to_string(c.getQuantity()) + " - " + c.getPhoto());
		QListWidgetItem *item = new QListWidgetItem(itemInList);
		this->repoList->addItem(item);
	}

	if (this->currentCoatsInRepoList.size() > 0)
		this->repoList->setCurrentRow(0);
}


