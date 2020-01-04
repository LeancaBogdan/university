#pragma once
#include "OfferRepo.h"
#include <stdlib.h>
#include <string.h>

OfferRepo * createRepo(int capacity)
{
	OfferRepo* repo = (OfferRepo*)malloc(sizeof(OfferRepo));
	if (!repo)
	{
		return NULL;
	}
	repo->capacity = capacity;
	repo->len = 0;
	repo->offers = (Offer**)malloc(sizeof(Offer*) * capacity);
	if (!repo->offers)
	{
		free(repo);
		return NULL;
	}

	return repo;
}

void destroyRepo(OfferRepo * repo)
{
	for (int i = 0; i < repo->len; i++)
		destroyOffer(repo->offers[i]);
	free(repo->offers);
	free(repo);
}

void decreaseLen(OfferRepo* repo)
{
	repo->len = repo->len - 1;
}

OfferRepo* checkSize(OfferRepo *repo)
{
	if (repo->len == 0)
		return repo;
	if (repo->len == repo->capacity)
	{
		OfferRepo *newRepo = (OfferRepo*)malloc(sizeof(OfferRepo));
		if (!newRepo)
		{
			return repo;
		}
		newRepo->offers = (Offer**)realloc(repo->offers, sizeof(Offer*) * repo->capacity * 2);
		if (!newRepo->offers)
		{
			free(newRepo);
			return repo;
		}
		newRepo->capacity = repo->capacity * 2;
		newRepo->len = repo->len;
		repo = newRepo;
	}
	if (repo->len <= repo->capacity / 4)
	{
		OfferRepo *newRepo = (OfferRepo*)malloc(sizeof(OfferRepo));
		if (!newRepo)
		{
			return repo;
		}
		newRepo->offers = (Offer**)realloc(repo->offers, sizeof(Offer*) * repo->capacity / 4);
		if (!newRepo->offers)
		{
			free(newRepo);
			return repo;
		}
		newRepo->capacity = repo->capacity / 4;
		newRepo->len = repo->len;
		repo = newRepo;
	}
	return repo;
}

Offer * find(OfferRepo * repo, char * address)
{
	for (int i = 0; i < repo->len; i++)
	{
		char *addr = getAddress(getOfferOnPos(repo, i));
		if (strcmp(addr, address) == 0)
			return repo->offers[i];
	}
	return NULL;
}

bool add(OfferRepo ** repo, Offer * o)
{
	if (find(*repo, o->address) != NULL)
		return false;
	*repo = checkSize(*repo);
	(*repo)->offers[(*repo)->len++] = o;

	return true;
}

bool removeO(OfferRepo** repo, char* address)
{
	if (find(*repo, address) == NULL)
		return false;
	
	int pos = -1;
	for (int i = 0; i < getLen(*repo); i++)
	{
		Offer* o = getOfferOnPos(*repo, i);
		if (strcmp(getAddress(o), address) == 0)
		{
			pos = i;
			break;
		}
	}
	destroyOffer((*repo)->offers[pos]);
	decreaseLen(*repo);
	for (int i = pos; i < getLen(*repo); i++)
		(*repo)->offers[i] = (*repo)->offers[i + 1];
	*repo = checkSize(*repo);
	return true;
}

bool update(OfferRepo* repo, char* address, char* type, int surface, int price)
{
	if (find(repo, address) != NULL)
		return false;

	int pos = -1;
	for (int i = 0; i < getLen(repo); i++)
		if (getAddress(repo->offers[i]) == address)
		{
			pos = i;
			break;
		}

	setType(repo->offers[pos], type);
	setSurface(repo->offers[pos], surface);
	setPrice(repo->offers[pos], price);
	return true;

}

int getLen(OfferRepo * repo)
{
	return repo->len;
}

Offer * getOfferOnPos(OfferRepo * repo, int pos)
{
	if (pos < 0 || pos >= repo->len)
		return NULL;
	return repo->offers[pos];
}

