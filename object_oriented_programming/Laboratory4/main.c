#include "UI.h"
#include <crtdbg.h>

int main()
{
	//TESTS
	testsOffersRepo();
	testsCont();

	Offers* repo = createRepo(10);
	OperationsStack* operationsStack = createStack();
	OperationsStack *redoStack = createStack();
	Controller* cont = createController(repo, operationsStack, redoStack);
	UI* ui = createUI(cont);

	int res = addOffer(cont, "Teodor Mihali", "apartment", 100, 49);
	res = addOffer(cont, "Observator", "apartment", 400, 100);
	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}