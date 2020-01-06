#include "Tests.h"
#include <assert.h>
#include <fstream>

Tests::Tests()
{
	this->c1 = Coat{ 15, "White", 500, 10, "test1.net" };
	this->c2 = Coat{ 20, "Black", 700, 15, "test2.net" };
	this->repo = Repository{};
	this->repo.addToRepository(c1);
	this->repo.addToRepository(c2);
	this->cont = Controller{ repo };
}


Tests::~Tests()
{
}

void Tests::testAll()
{
	this->testCoat();
	this->testRepo();
	this->testController();
	std::ofstream file("Tests.txt");
	file << "";
	file.close();
}

void Tests::testCoat()
{
	assert(this->c1.getSize() == 15);
	assert(this->c1.getColour() == "White");
	assert(this->c1.getPrice() == 500);
	assert(this->c1.getQuantity() == 10);
	assert(this->c1.getPhoto() == "test1.net");

	Coat c1{ 25, "Test", 200, 15, "test.net" };
	
	c1.setSize(15);
	assert(c1.getSize() == 15);

	c1.setColour("White");
	assert(c1.getColour() == "White");

	c1.setPrice(250);
	assert(c1.getPrice() == 250);

	c1.setQuantity(20);
	assert(c1.getQuantity() == 20);
	c1.increaseQuantity();
	assert(c1.getQuantity() == 21);
	c1.decreaseQuantity();
	assert(c1.getQuantity() == 20);

	c1.setPhoto("test1.net");
	assert(c1.getPhoto() == "test1.net");
	assert(this->c1 == c1);

	this->c1.showPhoto();
	Coat c2;
	c2 = this->c1;
	assert(c2.getPhoto() == this->c1.getPhoto());
	return;
}

void Tests::testRepo()
{
	std::vector<Coat> list = this->repo.getListInRepository();
	assert(list[0].getPhoto() == "test1.net");

	assert(this->repo.getRepositoryLength() == 2);

	assert(this->repo.getCoatBySizeAndColour(15, "White").getPhoto() == "test1.net");

	this->repo.removeFromRepository(this->c2);

	Coat c3{ 15, "White", 150, 70, "test3.net" };
	this->repo.updateInRepository(c3);
	assert(this->repo.getCoatBySizeAndColour(15, "White").getPrice() == 150);
	assert(this->repo.getCoatBySizeAndColour(15, "White").getQuantity() == 70);
	assert(this->repo.getCoatBySizeAndColour(15, "White").getPhoto() == "test3.net");

	assert(this->repo.getPointerToCoatBySizeAndColour(15, "White")->getColour() == "White");
	assert(this->repo.getPointerToCoatBySizeAndColour(20, "Yellow") == nullptr);

	Coat c4{ 15, "White", 150, 0, "test3.net" };
	this->repo.updateInRepository(c4);
	return;
}

void Tests::testController()
{
	this->cont.addController(17, "Test", 300, 15, "testAddC.net");

	this->repo.addToRepository(this->c2);
	this->cont.removeController(17, "Test");

	this->cont.updateController(15, "White", 1000, 30, "testUpdate.net");

	assert(this->cont.getListInController().size() == 2);
	
	assert(this->cont.filterRepoBySize(15).size() == 1);
	assert(this->cont.filterRepoBySize(20).size() == 1);

	this->cont.addToBasket(this->c1);
	assert(this->cont.getSumInBasket() == 500);
	assert(this->cont.getListInBasket()[0].getPhoto() == "test1.net");
	assert(this->cont.getListInBasket()[0].getQuantity() == 1);

	this->cont.addToBasket(this->c1);
	assert(this->cont.getListInBasket()[0].getQuantity() == 2);
	return;
}
