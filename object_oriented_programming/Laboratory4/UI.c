#include "UI.h"
#include <stdlib.h>
#include <stdio.h>

UI * createUI(Controller * cont)
{
	UI *ui = (UI*)malloc(sizeof(UI));
	if (!ui)
	{
		return NULL;
	}
	ui->cont = cont;
	return ui;
}

void destroyUI(UI * ui)
{
	destroyController(ui->cont);
	free(ui);
}

void printMenu()
{
	printf("\n*************************************************\n");
	printf("1. Add an offer\n");
	printf("2. Delete an offer\n");
	printf("3. Update an offer\n");
	printf("4. List all offers\n");
	printf("5. List offers with a given address\n");
	printf("6. List offers with a given type, having the surface greater than a given value\n");
	printf("7. Undo\n");
	printf("8. Redo\n");
	printf("9. Display all offers of a given type, sorted ascending by address\n");
	printf("0. Exit\n");
	printf("**************************************************\n");
}

int validCommand(int command)
{
	if (command >= 0 && command <= 9)
		return 1;
	return 0;
}

int readInteger(const char* message)
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

		r = sscanf_s(s, "%d", &res);
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

void readStringWithSpaces(const char *message, int maxStrSize, char *str)
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	int size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}

int addOfferUI(UI *ui)
{
	char type[11], address[100];
	int surface = -1, price = -1;
	printf("Please input the type (apartment, house or penthouse): ");
	scanf_s("%11s", type, 11);
	fgetc(stdin);
	readStringWithSpaces("Please input the address: ", 100, address);
	printf("Please input the price: ");
	scanf_s("%d", &price);
	printf("Please input the surface: ");
	scanf_s("%d", &surface);

	return addOffer(ui->cont, address, type, price, surface);
}

int deleteOfferUI(UI *ui)
{
	char address[100];
	fgetc(stdin);
	readStringWithSpaces("Please input the address: ", 100, address);
	return deleteOffer(ui->cont, address);
}

int updateOfferUI(UI *ui)
{
	char type[11], address[100];
	int surface = -1, price = -1;
	printf("Please input the type (apartment, house or penthouse): ");
	scanf_s("%11s", type, 11);
	fgetc(stdin);
	readStringWithSpaces("Please input the address: ", 100, address);
	printf("Please input the price: ");
	scanf_s("%d", &price);
	printf("Please input the surface: ");
	scanf_s("%d", &surface);

	return updateOffer(ui->cont, address, type, price, surface);
}

void listAllOffers(UI *ui)
{
	Offers *repo = getRepo(ui->cont);
	int len = repoGetLength(repo);
	if (len == 0)
	{
		printf("There are no stored offers!\n");
		return;
	}
	for (int i = 0; i < len; i++)
	{
		char str[500];
		toString(getOfferOnPos(repo, i), str, i + 1);
		printf("%s\n", str);
	}
}

void listOffersWithAddress(UI *ui)
{
	char address[100];
	fgetc(stdin);
	readStringWithSpaces("Please input the address (input 'null' for no address): ", 100, address);
	Offers *res = filterByAddress(ui->cont, address);
	int len = repoGetLength(res);
	if (len == 0)
	{
		printf("There are no offers with the given address!\n");
		return;
	}
	for (int i = 0; i < len; i++)
	{
		char str[500];
		toString(getOfferOnPos(res, i), str, i + 1);
		printf("%s\n", str);
	}
	//destroyRepo(res);
}

void listOffersWithType(UI *ui)
{
	char type[11];
	printf("Please input the type: ");
	scanf_s("%11s", type, 11);
	Offers *res = filterByType(ui->cont, type);
	int len = repoGetLength(res);
	if (len == 0)
	{
		printf("There are no offers with the given type!\n");
		return;
	}
	int surface = -1;
	printf("Please input the surface: ");
	scanf_s("%d", &surface);
	for (int i = 0; i < len; i++)
	{
		if (getSurface(getOfferOnPos(res, i)) > surface)
		{
			char str[500];
			toString(getOfferOnPos(res, i), str, i + 1);
			printf("%s\n", str);
		}
	}
	//destroyRepo(res);
}

void labActivity(UI *ui)
{
	char type[11];
	printf("Please input the type: ");
	scanf_s("%11s", type, 11);
	Offers *res = filterByType(ui->cont, type);
	int len = repoGetLength(res);
	if (len == 0)
	{
		printf("There are no offers with the given type!\n");
		return;
	}
	sortByAddress(res);
	for (int i = 0; i < res->len; i++)
	{
		char str[500];
		toString(getOfferOnPos(res, i), str, i + 1);
		printf("%s\n", str);
	}
	//destroyRepo(res);
}

void startUI(UI * ui)
{
	while (1)
	{
		printMenu();
		int command = readInteger("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readInteger("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = addOfferUI(ui);
			if (res == 1)
				printf("Offer successfully added!\n");
			else
				printf("Error! Offer could not be added, as there is another offer with the same address!\n");
			break;
		}
		case 2:
		{
			int res = deleteOfferUI(ui);
			if (res == 1)
				printf("Offer successfully removed!\n");
			else
				printf("Error! Offer could not be removed, as there is no offer with the given address stored!\n");
			break;
		}
		case 3:
		{
			int res = updateOfferUI(ui);
			if (res == 1)
				printf("Offer successfully updated!\n");
			else
				printf("Error! Offer could not be updated, as there is no offer with the given address stored!\n");
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
		case 6:
		{
			listOffersWithType(ui);
			break;
		}
		case 7:
		{
			int res = undo(ui->cont);
			if (res == 1)
				printf("Undo successful!\n");
			else
				printf("There is no operation to undo!\n");
			break;
		}
		case 8:
		{
			int res = redo(ui->cont);
			if (res == 1)
				printf("Redo successful!\n");
			else
				printf("There is no operation to redo!\n");
			break;
		}
		case 9:
		{
			labActivity(ui);
			break;
		}
		}
	}
}
