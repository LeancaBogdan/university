#pragma once
#include "Offer.h"

typedef struct
{
	Offer** offers;
	int len;
	int capacity;
} OfferRepo;

OfferRepo* createRepo(int capacity);
void destroyRepo(OfferRepo* repo);

Offer* find(OfferRepo* repo, char* address);

bool add(OfferRepo** repo, Offer* o);
bool removeO(OfferRepo** repo, char* address);
bool update(OfferRepo* repo, char* address, char* type, int size, int price);

int getLen(OfferRepo* repo);

Offer* getOfferOnPos(OfferRepo* repo, int pos);


