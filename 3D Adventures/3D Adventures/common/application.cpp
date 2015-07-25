#include "application.hpp"




#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FULLSCREEN false





int Application::Init()
{





	return 1;


}




void Application::SetFlags()
{


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);



}





void Application::Load(char *path)
{


	SetManager(NULL);



	Controller * ctrl = static_cast<Controller*>
		(Add("Controller", new Controller(WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN, "3D Adventures 0.2.5", 4, 3)));
	     ctrl->Load(path);


    root_ui = new RootUI(ctrl);
	pipe = new Pipeline(ctrl);


}





void Application::Render()
{


	Controller * ctrl = static_cast<Controller*>(Get("Controller"));


	do{




		Enable();
		pipe->Render(ctrl);


		glfwSwapBuffers(ctrl->GetWindow());
		glfwPollEvents();



	} while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
		!glfwWindowShouldClose(ctrl->GetWindow()));


}





void Application::Terminate()
{


	Clean();
	delete pipe;


}




