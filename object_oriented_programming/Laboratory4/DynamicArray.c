#include "DynamicArray.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = (DynamicArray*)malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	// allocate space for the elements
	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// free the space allocated for the elements
	free(arr->elems);
	arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
	arr = NULL;
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	TElement* newBuffer = NULL;
	arr->capacity *= 2;
	newBuffer = (TElement*)realloc(arr->elems, arr->capacity * sizeof(TElement));
	if (newBuffer)
	{
		arr->elems = newBuffer;
	}
}

void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	// resize the array, if necessary
	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length++] = t;
}

void delete(DynamicArray* arr, int pos)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	for (int i = pos; i < arr->length - 1; i++)
		arr->elems[i] = arr->elems[i + 1];

	arr->length--;
}

int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return -1;

	return arr->length;
}

TElement get(DynamicArray* arr, int pos)
{
	return arr->elems[pos];
}

// ------------------------------------------------------------------------------------------------------------
// Tests

void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->length == 0);

	Offer* o1 = createOffer("house", "100 Infinite Loop", 1000, 250000);
	add(da, o1);
	assert(da->length == 1);

	Offer* o2 = createOffer("apartment", "2 Calea Manastur", 50, 500);
	add(da, o2);
	assert(da->length == 2);

	// capacity must double
	Offer* o3 = createOffer("penthouse", "Buna Ziua", 100, 1000);
	add(da, o3);
	assert(da->length == 3);
	assert(da->capacity == 4);

	// delete offer on position 0
	delete(da, 0);
	Offer* o = get(da, 0);
	assert(strcmp(getAddress(o), "2 Calea Manastur") == 0);
	assert(da->length == 2);

	// destroy the dynamic array
	destroy(da);

	// destroy the offers
	destroyOffer(o1);
	destroyOffer(o2);
	destroyOffer(o3);
}