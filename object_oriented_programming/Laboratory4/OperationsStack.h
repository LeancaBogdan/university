#pragma once
#include "Offer.h"
#include <string.h>

typedef struct
{
	Offer* offer;
	char* operationType;
} Operation;

/*
------------------------------------------------------------------
Creates an operation
Input: of - pointer to the offer that was changed
	   operationType - pointer to a string containing the type of operation to be undone
Return: pointer to the operation
------------------------------------------------------------------
*/
Operation* createOperation(Offer* of, char* operationType);

/*Destroys an operation
Input: o - pointer to the operation to be destroyed
Return: -
------------------------------------------------------------------
*/
void destroyOperation(Operation* o);

/*
------------------------------------------------------------------
Makes a deep copy of an operation
Input: o - pointer to the operation to be copied
Return: pointer to the copy
------------------------------------------------------------------
*/
Operation* copyOperation(Operation* o);

/*
------------------------------------------------------------------
Getter for the type of an operation
Input: o - pointer to the operation
Return: pointer to a string containing the type of the operation
------------------------------------------------------------------
*/
char* getOperationType(Operation* o);

/*
-------------------------------------------------------------------
Getter for the offer affected by the operation
Input: o - pointer to the operation
Return: pointer to the offer
-------------------------------------------------------------------
*/
Offer* getOffer(Operation* o);

// ---------------------------------------------------------------
typedef struct
{
	Operation* operations[100];
	int length;
} OperationsStack;

/*
--------------------------------------------------------------------
Creates a stack
Input: -
Return: Pointer to the begining of the stack
--------------------------------------------------------------------
*/
OperationsStack* createStack();

/*
Destroys a stack
Input: s - pointer to the begining of the stack
Return: -
--------------------------------------------------------------------
*/
void destroyStack(OperationsStack* s);

/*
--------------------------------------------------------------------
Pushes an operation on top of the stack
Input: s - pointer to the begining of the stack
	   o - pointer to the operation to be pushed onto the stack
Return: -
--------------------------------------------------------------------
*/
void push(OperationsStack* s, Operation* o);

/*
--------------------------------------------------------------------
Pops the operation from the top of the stack
Input: s - pointer to the begining of the stack
Return: pointer to the operation popped
--------------------------------------------------------------------
*/
Operation* pop(OperationsStack* s);

/*
-------------------------------------------------------------------
Checks if the stack is empty
Input: s - pointer to the begining of the stack
Return: 1 - If the stack is empty
		0 - If the stack is not-empty
-------------------------------------------------------------------
*/
int isEmpty(OperationsStack* s);

/*
--------------------------------------------------------------------
Checks if the stack is full
Input: s - pointer to the begining of the stack
Return: 1 - If the stack is full
		0 - If the stack is not full
--------------------------------------------------------------------
*/
int isFull(OperationsStack* s);
