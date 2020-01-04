#include "UI.h"

UI* createUI(Controller * c)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	if (!ui)
	{
		return NULL;
	}
	ui->cont = c;

	return ui;
}

void destroyUI(UI * ui)
{
	destroyController(ui->cont);
	free(ui);
}

void printMenu()
{
	printf("\n1. Add an offer\n");
	printf("2. Delete an offer\n");
	printf("3. Update an offer\n");
	printf("4. List all offers\n");
	printf("5. List offers whose address contains a given string\n");
	printf("0. Exit\n");
}

bool validCommand(int command)
{
	if (command >= 0 && command <= 5)
		return true;
	return false;
}

int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf_s("%s", s, 15);
		s[15] = 0;

		r = sscanf_s(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

bool addOfferUI(UI* ui)
{
	char *type = (char*)malloc(11*sizeof(char)), *address = (char*)malloc(100*sizeof(char));
	int surface = 0, price = 0;
	printf("Please enter a type (house, apartment or penthouse): ");
	scanf_s("%11s", type, 11);
	printf("Please input the address: ");
	scanf_s("%100s", address, 100);
	printf("Please input the surface: ");
	scanf_s("%d", &surface);
	printf("Please input the price: ");
	scanf_s("%d", &price);
	bool res = addOffer(ui->cont, address, type, surface, price);
	return res;
}

bool removeOfferUI(UI* ui)
{
	char address[100];
	printf("Please give the address: ");
	scanf_s("%100s", address, 100);
	
	return removeOffer(ui->cont, address);
}

bool updateOfferUI(UI* ui)
{
	char type[11], address[100];
	int surface = 0, price = 0;
	printf("Please enter a type (house, appartment or penthouse): ");
	scanf_s("%11s", type, 11);
	printf("Please input the address: ");
	scanf_s("%100s", address, 100);
	printf("Please input the surface: ");
	scanf_s("%d", &surface);
	printf("Please input the price: ");
	scanf_s("%d", &price);

	return updateOffer(ui->cont, address, type, surface, price);
}

void listAllOffers(UI* ui)
{
	OfferRepo* repo = getRepo(ui->cont);
	int len = getLen(repo);

	if (len == 0)
	{
		char* str = "There are no stored offers!";
		printf("%s \n", str);
	}

	for (int i = 0; i < len; i++)
	{
		char *str = (char*)malloc(sizeof(char) * 500);
		toString(getOfferOnPos(repo, i), str, i);
		printf("%s\n", str);
		free(str);
	}
}

int comp(const Offer* const o1, const Offer* const o2)
{
	if (o1->price > o2->price) return 1;
	if (o1->price < o2->price) return -1;
	return 0;
}

void listOffersWithAddress(UI* ui)
{
	char address[100];
	printf("Please input the address; input 'null' for no address: ");
	scanf_s("%s", address, 100);

	OfferRepo* res = filterByAddress(ui->cont, address);
	int len = getLen(res);
	if (len == 0)
		printf("There are no offers with the given address!\n");
	else
	{
		qsort(res, len, sizeof(Offer), comp);
		for (int i = 0; i < len; i++)
		{
			char *str = (char*)malloc(500 * sizeof(char));
			toString(getOfferOnPos(res, i), str, i);
			printf("Offer on pos %d: %s\n", i, str);
			free(str);
		}
	}
	destroyRepo(res);
}

void startUI(UI * ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Choose a command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Choose a command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			bool res = addOfferUI(ui);
			if (res == 1)
				printf("Offer successfully added!\n");
			else
				printf("Error! There is another offer of a property at the same address or you have entered an invalid type!\n");
			break;
		}
		case 2:
		{
			bool res = removeOfferUI(ui);
			if (res == 1)
				printf("Offer successfully removed!\n");
			else
				printf("Error! Offer with the given address not in the repo!\n");
			break;
		}
		case 3:
		{
			bool res = updateOfferUI(ui);
			if (res == 1)
				printf("Offer successfully updated!\n");
			else
				printf("Error! Offer with the given address not in the repo!\n");
			break;
		}
		case 4:
		{
			listAllOffers(ui);
			break;
		}
		case 5:
		{
			listOffersWithAddress(ui);
			break;
		}
		}
	}
}
