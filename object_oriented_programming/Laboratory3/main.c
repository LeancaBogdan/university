#include "OfferRepo.h"
#include "UI.h"
#include <crtdbg.h>

int main()
{
	OfferRepo* repo = createRepo(1);
	if (!repo)
	{
		exit(1);
	}
	Controller* cont = createController(repo);
	UI* ui = createUI(cont);

	addOffer(cont, "asd", "house", 10, 1000);
	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}