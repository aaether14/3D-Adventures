#include "application.hpp"




#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FULLSCREEN false





int Application::Init()
{


	ctrl = new Controller(WINDOW_WIDTH, WINDOW_HEIGHT, FULLSCREEN, "3D Adventures 0.1.6", 4, 3);
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


	ctrl->Load(path);
	pipe = new Pipeline(ctrl);
	root_ui = new RootUI(ctrl);


}





void Application::Render()
{


	do{



		ctrl->Enable();
		pipe->Render(ctrl);
		root_ui->Render(ctrl);



		glfwSwapBuffers(ctrl->GetWindow());
		glfwPollEvents();



	} while (!ctrl->GetKey(GLFW_KEY_ESCAPE) &&
		!glfwWindowShouldClose(ctrl->GetWindow()));


}





void Application::Terminate()
{



	delete pipe;
	delete ctrl;
	delete root_ui;


}




