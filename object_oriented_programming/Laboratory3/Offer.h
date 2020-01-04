#pragma once
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
	char *type;
	char *address;
	int surface;
	int price;
} Offer;

Offer* createOffer(char* type, char* address, int surface, int price);
void destroyOffer(Offer* o);

char* getType(Offer* o);
bool setType(Offer* o, char* type);

char* getAddress(Offer* o);
void setAddress(Offer* o, char* address);

int getSurface(Offer* o);
void setSurface(Offer* o, int surface);

int getPrice(Offer* o);
void setPrice(Offer* o, int price);

void toString(Offer* o, char* str, int i);