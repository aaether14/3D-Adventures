#include "data_manager.hpp"



void DataManager::Init()
{



	ControllerSource * controller_source = static_cast<ControllerSource*>(GetManager()->Get("Controller"));
	GLuint window_width = controller_source->GetWindowWidth();
	GLuint window_height = controller_source->GetWindowHeight();



	GLuint dof_factor = 2;
	GLuint bright_factor = 2;
	this->techniques = new Techniques();
	this->techniques->Create(window_width, window_height, ShadowMapWidth, ShadowMapHeight,
		window_width / dof_factor, window_height / dof_factor,
		window_width / bright_factor, window_height / bright_factor);




	res = new ResourceLoader();
	res->LoadResourcePaths(AString::char_to_str("map1.AAETHER"));
	res->Add("Environment", new Environment(res->GetEnvFile()));
	res->Add("FilterSettings", new FilterSettings(res->GetFSettingsFile()));
	res->Add("Entities", new SceneInfo(res->GetSceneFile()));
	res->LoadChanges();




}




void DataManager::Enable()
{



	ControllerSource * ctrl = static_cast<ControllerSource*>(GetManager()->Get("Controller"));


	if (ctrl->GetDropFiles().size() > 0)
	{


	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


	scene_info->InsertNewEntity(ctrl->GetDropFiles()[0]);
	ctrl->ResetDropList();


	}


}


void DataManager::Clean()
{



	if (res)
	delete this->res;


	if (techniques)
	delete this->techniques;


}




GLuint DataManager::GetInd(glm::vec3 pos)
{


	if (q_tree)
		return GLuint(pos.z / q_tree->GetMinZ())*q_tree->GetWidth() +
		GLuint(pos.x / q_tree->GetMinX());


}