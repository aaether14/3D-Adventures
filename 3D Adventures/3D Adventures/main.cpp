#include <application.hpp>




int main(int argc, char *argv[])
{



	Application*app = new Application();


	app->SetFlags();

	if (argc > 1)
		app->Load(argv[1]);
	else
		app->Load("map1.AAETHER");

	app->Render();


	delete app;


	return 0;



}
