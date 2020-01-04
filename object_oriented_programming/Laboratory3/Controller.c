#include "Controller.h"
#include <string.h>

Controller * createController(OfferRepo * repo)
{
	Controller* cont = (Controller*)malloc(sizeof(Controller));
	if (!cont)
	{
		return NULL;
	}
	cont->repo = repo;

	return cont;
}

void destroyController(Controller * cont)
{
	destroyRepo(cont->repo);
	free(cont);
}

bool addOffer(Controller * cont, char * address, char * type, int surface, int price)
{
	Offer* o = createOffer(type, address, surface, price);
	if (o == NULL)
		return false;

	return add(&cont->repo, o);
}

bool removeOffer(Controller* cont, char* address)
{
	return removeO(&cont->repo, address);
}

bool updateOffer(Controller * cont, char * address, char * type, int surface, int price)
{
	return update(cont->repo, address, type, surface, price);
}

OfferRepo * getRepo(Controller * cont)
{
	return cont->repo;
}

OfferRepo * filterByAddress(Controller * cont, char * address)
{
	OfferRepo* res = createRepo(1);
	if (strcmp(address, "null") == 0)
		return getRepo(cont);

	for (int i = 0; i < getLen(cont->repo); i++)
	{
		Offer* o = getOfferOnPos(cont->repo, i);
		if (strstr(o->address, address) != NULL)
		{
			Offer* newOffer = createOffer(o->type, o->address, o->surface, o->price);
			add(&res, newOffer);
		}
	}

	return res;
}

