#include "Controller.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Controller * createController(Offers * repo, OperationsStack *undoS, OperationsStack *redoS)
{
	Controller *cont = (Controller*)malloc(sizeof(Controller));
	if (!cont)
		return NULL;
	cont->repo = repo;
	cont->undoStack = undoS;
	cont->redoStack = redoS;
	return cont;
}

void destroyController(Controller * cont)
{
	destroyRepo(cont->repo);
	destroyStack(cont->undoStack);
	destroyStack(cont->redoStack);
	free(cont);
}

int addOffer(Controller * cont, char * address, char * type, int price, int surface)
{
	Offer *of = createOffer(address, type, price, surface);
	int res = addR(cont->repo, of);
	if (res == 1)
	{
		Operation* o = createOperation(of, "add");
		push(cont->undoStack, o);
		destroyOperation(o);
	}
	return res;
}

int deleteOffer(Controller *cont, char *address)
{
	Offer *of = copyOffer(getOfferOnPos(getRepo(cont), getPos(getRepo(cont), address)));
	int res = deleteR(cont->repo, address);
	if (res == 1)
	{
		Operation *o = createOperation(of, "remove");
		push(cont->undoStack, o);
		destroyOperation(o);
	}
	destroyOffer(of);
	return res;
}

int updateOffer(Controller *cont, char *address, char *type, int price, int surface)
{
	Offer *of = copyOffer(getOfferOnPos(cont->repo, getPos(cont->repo, address)));
	int res = updateR(cont->repo, address, type, price, surface);
	if (res == 1)
	{
		Operation *o = createOperation(of, "update");
		push(cont->undoStack, o);
		destroyOperation(o);
	}
	destroyOffer(of);
	return res;
}

Offers * getRepo(Controller * cont)
{
	return cont->repo;
}

Offers * filterByAddress(Controller * cont, char * search)
{
	Offers *res = createRepo(10);
	if (strcmp(search, "null") == 0)
		return cont->repo;
	for (int i = 0; i < repoGetLength(cont->repo); i++)
	{
		Offer *o = getOfferOnPos(cont->repo, i);
		if (strstr(getAddress(o), search) != NULL)
			addR(res, o);
	}
	return res;
}

Offers *filterByType(Controller *cont, char *search)
{
	{
		Offers *res = createRepo(10);
		for (int i = 0; i < repoGetLength(cont->repo); i++)
		{
			Offer *o = getOfferOnPos(cont->repo, i);
			if (strcmp(getType(o), search) == 0)
				addR(res, o);
		}
		return res;
	}
}

int redo(Controller *cont)
{
	if (isEmpty(cont->undoStack))
	{
		return 0;
	}
	
	Operation *operation = pop(cont->redoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Offer *o = getOffer(operation);
		int res = addR(cont->repo, o);
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Offer *o = getOffer(operation);
		char address[100];
		strcpy_s(address, 100, getAddress(o));
		int res = deleteR(cont->repo, address);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Offer *o = getOffer(operation);
		int res = updateR(cont->repo, getAddress(o), getType(o), getPrice(o), getSurface(o));
	}
	destroyOperation(operation);
	return 1;
}

int undo(Controller* cont)
{
	if (isEmpty(cont->undoStack))
	{
		return 0;
	}

	Operation* operation = pop(cont->undoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{

		Offer *o = getOffer(operation);
		char address[100];
		strcpy_s(address, 100, getAddress(o));
		int res = deleteR(cont->repo, address);
		if (res == 1)
		{
			Operation *op = createOperation(o, "add");
			push(cont->redoStack, op);
			destroyOperation(op);
		}
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Offer *o = getOffer(operation);
		int res = addR(cont->repo, o);
		if (res == 1)
		{
			Operation *op = createOperation(o, "remove");
			push(cont->redoStack, op);
			destroyOperation(op);
		}
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Offer *o = getOffer(operation);
		int res = updateR(cont->repo, getAddress(o), getType(o), getPrice(o), getSurface(o));
		if (res == 1)
		{
			Offer *o2 = getOfferOnPos(cont->repo, getPos(cont->repo, getAddress(o)));
			Operation *op = createOperation(o2, "update");
			push(cont->undoStack, op);
			destroyOperation(op);
		}
	}
	destroyOperation(operation);

	return 1;
}

int compare(const void *o1, const void *o2)
{
	Offer *op1 = (Offer*)o1;
	Offer *op2 = (Offer*)o2;
	return strcmp(getAddress(op1), getAddress(op2));
}

void sortByAddress(Offers *repo)
{
	for (int i = 0; i < repo->len - 1; i++)
	{
		for (int j = i + 1; j < repo->len; j++)
		{
			if (compare(getOfferOnPos(repo, i), getOfferOnPos(repo, j))>0) 
			{
				Offer *o = copyOffer(getOfferOnPos(repo, i));
				repo->offers[i] = repo->offers[j];
				repo->offers[j] = o;
			}
		}
	}
}
//TESTS
void testCont()
{
	Offers *repo = createRepo(10);
	OperationsStack *opS = createStack();
	OperationsStack *redoS = createStack();
	Controller *cont = createController(repo, opS, redoS);

	int res = addOffer(cont, "Teodor Mihali", "apartment", 450, 80);
	assert(res == 1);
	assert(repoGetLength(repo) == 1);
	char* currentAddress = getAddress(getOfferOnPos(getRepo(cont), 0));
	assert(strcmp(currentAddress, "Teodor Mihali") == 0);
	undo(cont);
	assert(repoGetLength(getRepo(cont)) == 0);

	assert(addOffer(cont, "Obs 136", "penthouse", 500, 120) == 1);
	assert(repoGetLength(repo) == 1);

	// now try to add the same offer again -> add must return 0
	assert(addOffer(cont, "Obs 136", "penthouse", 500, 120) == 0);
	assert(repoGetLength(repo) == 1);

	deleteOffer(cont, "Obs 136");
	assert(repoGetLength(repo) == 0);
	undo(cont);
	assert(repoGetLength(cont->repo) == 1);

	destroyController(cont);
}

void testsCont()
{
	testCont();
}