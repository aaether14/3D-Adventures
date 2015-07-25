#include <application.hpp>




int main(int argc, char *argv[])
{



	Application*app = new Application();
	app->Load("map1.AAETHER");
	app->Enable();


	delete app;


	return 0;



}
