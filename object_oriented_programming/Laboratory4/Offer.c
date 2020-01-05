#include "Offer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Offer* createOffer(char *address, char *type, int price, int surface)
{
	Offer *o = (Offer*)malloc(sizeof(Offer));
	if (!o)
	{
		return NULL;
	}
	strcpy_s(o->address, 100, address);
	strcpy_s(o->type, 11, type);
	o->price = price;
	o->surface = surface;
	return o;
}

void destroyOffer(Offer *o)
{
	free(o);
}

Offer* copyOffer(Offer* o)
{
	if (o == NULL)
		return NULL;

	Offer* newOffer = createOffer(getAddress(o), getType(o), getPrice(o), getSurface(o));
	return newOffer;
}

char *getAddress(Offer *o)
{
	return o->address;
}

char *getType(Offer *o)
{
	return o->type;
}

int getSurface(Offer *o)
{
	return o->surface;
}

int getPrice(Offer *o)
{
	return o->price;
}

void setAddress(Offer *o, char *address)
{
	strcpy_s(o->address, 100, address);
}

void setType(Offer *o, char *type)
{
	strcpy_s(o->type, 11, type);
}

void setSurface(Offer *o, int surface)
{
	o->surface = surface;
}

void setPrice(Offer *o, int price)
{
	o->price = price;
}

void toString(Offer * o, char * str, int i)
{
	sprintf_s(str, 500, "Offer no. %d is of type %s, has address %s, has %d square meters and costs %d dollars.\n", i, o->type, o->address, o->surface, o->price);
}
