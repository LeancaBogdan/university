#pragma once
#include "OfferRepo.h"

typedef struct
{
	OfferRepo* repo;
} Controller;

Controller* createController(OfferRepo* repo);
void destroyController(Controller* cont);

bool addOffer(Controller* cont, char* address, char* type, int surface, int price);
bool removeOffer(Controller* cont, char* address);
bool updateOffer(Controller* cont, char* address, char* type, int surface, int price);

OfferRepo* getRepo(Controller* cont);

OfferRepo* filterByAddress(Controller* cont, char* address);
