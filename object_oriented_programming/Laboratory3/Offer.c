#include "Offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool valid(char* type)
{
	if (strcmp(type, "house") == 0 || strcmp(type, "apartment") == 0 || strcmp(type, "penthouse") == 0)
		return true;
	return false;
}

Offer * createOffer(char * type, char * address, int surface, int price)
{
	Offer* o = (Offer*)malloc(sizeof(Offer));
	if (o == NULL)
		return NULL;

	o->type = (char*)malloc(strlen(type) + 1);
	if (!o->type)
		return NULL;
	strcpy_s(o->type, strlen(type) + 1, type);

	o->address = (char*)malloc(strlen(address) + 1);
	if (!o->address)
		return NULL;
	strcpy_s(o->address, strlen(address) + 1, address);

	o->price = price;
	o->surface = surface;

	return o;
}

void destroyOffer(Offer * o)
{
	free(o->address);
	free(o->type);

	free(o);
}

char * getType(Offer * o)
{
	return o->type;
}

bool setType(Offer * o, char * type)
{
	char* buffer = NULL;

	if (!valid(type))
		return false;

	buffer = o->type;
	o->type = (char*)malloc(strlen(type) + 1);
	if (!o->type)
	{
		o->type = buffer;
		return false;
	}
	strcpy_s(o->type, strlen(type) + 1, type);

	free(buffer);
	return true;
}

char * getAddress(Offer * o)
{
	return o->address;
}

void setAddress(Offer * o, char * address)
{
	char* buffer = o->address;
	o->address = (char*)malloc(strlen(address) + 1);
	if (!o->address)
	{
		o->address = buffer;
		return;
	}
	strcpy_s(o->address, strlen(address) + 1, address);
	free(buffer);
}

int getSurface(Offer * o)
{
	return o->surface;
}

void setSurface(Offer * o, int surface)
{
	o->surface = surface;
}

int getPrice(Offer * o)
{
	return o->price;
}

void setPrice(Offer * o, int price)
{
	o->price = price;
}

void toString(Offer * o, char * str, int i)
{
	sprintf_s(str, 500, "Offer no. %d is of type %s, has address %s, has %d square meters and costs %d dollars.\n", i, o->type, o->address, o->surface, o->price);
}


