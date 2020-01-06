#pragma once
#include "Coat.h"
#include "Repository.h"
#include "Controller.h"

class Tests
{
	Repository repo;
	Controller cont;
	Coat c1;
	Coat c2;

public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Tests"/> class.
	/// </summary>
	Tests();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Tests"/> class.
	/// </summary>
	~Tests();
		
	/// <summary>
	/// Runs all the tests.
	/// </summary>
	void testAll();

	/// <summary>
	/// Tests the <see cref="Coat"/> class.
	/// </summary>
	void testCoat();
	
	/// <summary>
	/// Tests the <see cref="Repository"/> class.
	/// </summary>
	void testRepo();
	
	/// <summary>
	/// Tests the <see cref="Controller"/> class.
	/// </summary>
	void testController();
};

