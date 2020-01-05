#include "OfferRepo.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Offers * createRepo(int capacity)
{
	Offers *repo = (Offers*)malloc(sizeof(Offers));
	if (repo == NULL)
		return NULL;
	repo->capacity = capacity;
	repo->len = 0;
	repo->offers = (Offer**)malloc(sizeof(Offer*) * capacity);
	if (repo->offers == NULL)
		return NULL;
	return repo;
}

void destroyRepo(Offers * repo)
{
	if (repo == NULL)
		return;
	for (int i = 0; i < repo->len; i++)
		destroyOffer(repo->offers[i]);

	free(repo->offers);
	repo->offers = NULL;
	free(repo);
	repo = NULL;
}

void repoResize(Offers *repo)
{
	if (repo == NULL)
		return;

	Offer** newBuffer = NULL;
	repo->capacity *= 2;
	newBuffer = (Offer**)realloc(repo->offers, repo->capacity * sizeof(Offer*));
	if (newBuffer)
		repo->offers = newBuffer;
		
}

int addR(Offers * repo, Offer * o)
{
	if (repo == NULL)
		return 0;
	if (repo->offers == NULL)
		return 0;
	if (repo->len == repo->capacity)
		repoResize(repo);
	if (-1 != getPos(repo, o->address))
	{
		return 0;
	}
	repo->offers[repo->len++] = o;
	return 1;
}

int deleteR(Offers * repo, char * address)
{
	if (repo == NULL)
		return 0;
	if (repo->offers == NULL)
		return 0;
	int pos = getPos(repo, address);
	if (pos == -1)
		return 0;
	destroyOffer(repo->offers[pos]);
	for (int i = pos; i < repo->len - 1; i++)
		repo->offers[i] = repo->offers[i + 1];
	repo->len--;
	return 1;
}

int updateR(Offers *repo, char *address, char *type, int price, int surface)
{
	if (repo == NULL)
		return 0;
	if (repo->offers == NULL)
		return 0;
	int pos = getPos(repo, address);
	if (pos == -1)
		return 0;
	Offer *o = getOfferOnPos(repo, pos);
	setType(o, type);
	setPrice(o, price);
	setSurface(o, surface);
	return 1;
}

int repoGetLength(Offers * repo)
{
	if (repo == NULL)
		return -1;
	return repo->len;
}

int getPos(Offers * repo, char * address)
{
	for (int i = 0; i < repo->len; i++)
		if (strcmp(getAddress(getOfferOnPos(repo, i)), address) == 0)
			return i;
	return -1;
}

Offer *getOfferOnPos(Offers *repo, int pos)
{
	return repo->offers[pos];
}

//TESTS
void testAll()
{
	Offers *repo = createRepo(10);

	Offer *o1 = createOffer("Teodor Mihali", "apartment", 450, 80);
	addR(repo, o1);
	assert(repoGetLength(repo) == 1);
	assert(strcmp(getAddress(getOfferOnPos(repo, 0)), "Teodor Mihali") == 0);

	Offer *o2 = createOffer("Observator", "penthouse", 500, 120);
	assert(addR(repo, o2) == 1);
	assert(repoGetLength(repo) == 2);

	// now try to add the same offer again -> add must return 0
	assert(addR(repo, o2) == 0);

	deleteR(repo, "Observator");
	assert(repoGetLength(repo) == 1);

	updateR(repo, "Teodor Mihali", "penthouse", 450, 80);
	char* typeToCheck = getType(getOfferOnPos(repo, 0));
	assert(strcmp(typeToCheck, "penthouse") == 0);

	// destroy the test repository
	destroyRepo(repo);
}

void testsOffersRepo()
{
	testAll();
}