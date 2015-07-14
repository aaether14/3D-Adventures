#include "controls.hpp"







void Controller::Init(GLint width, GLint height, GLboolean fullscreen, GLchar * title, GLuint major, GLuint minor)
{


	this->CreateWindow(width, height, fullscreen, title, major, minor);


	this->camera = new Camera();
	this->g_obj = new GameObject(GetWindowWidth(), GetWindowHeight());

	

}



void Controller::Load(char*path)
{



	ResourceLoader * res = g_obj->GetResource();
	Environment * env = g_obj->GetSettings()->GetEnv();
	FilterSettings * f_settings = g_obj->GetSettings()->GetFilterSettings();


	res->Load(path);
	env->Load(g_obj->GetResource()->GetEnvFile());
	f_settings->Load(g_obj->GetResource()->GetFSettingsFile());




}



void Controller::Clean()
{

	

	delete this->camera;
	delete this->g_obj;


	ControllerSource::Clean();


}






void Controller::Enable()
{



	ControllerSource::Enable();

	camera->ProcessInput(this);
	camera->ComputeAngles(this);
	camera->SetFrustum(camera->GetView()->getCamera());


}
