#include "application.hpp"




#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FULLSCREEN false








void Application::Init()
{


	SetManager(this);



}






void Application::Load(char *path)
{



	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);





	Add("Controller", new Controller(WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN, "3D Adventures 0.2.5", 4, 3));
	Controller * ctrl = static_cast<Controller*>(Get("Controller"));
	ctrl->Load(path);



	Add("RootUI", new RootUI());
	static_cast<RootUI*>(Get("RootUI"))->Init();



	Add("Pipeline", new Pipeline());
	static_cast<Pipeline*>(Get("Pipeline"))->Init();


}





void Application::Enable()
{



	Controller * ctrl = static_cast<Controller*>(Get("Controller"));


	do{


		Get("Controller")->Enable();
		Get("Pipeline")->Enable();
		Get("RootUI")->Enable();



		glfwSwapBuffers(ctrl->GetWindow());
		glfwPollEvents();



	} while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
		!glfwWindowShouldClose(ctrl->GetWindow()));


}





void Application::Clean()
{


	Get("Pipeline")->Clean();
	Get("Controller")->Clean();
	Get("RootUI")->Clean();


}




