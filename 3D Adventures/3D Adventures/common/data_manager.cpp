#include "data_manager.hpp"



void DataManager::Init()
{







	GLuint dof_factor = 2;
	GLuint bright_factor = 2;
	this->techniques = new Techniques();
	this->techniques->Create(800, 600, ShadowMapWidth, ShadowMapHeight,
		800 / dof_factor, 600 / dof_factor,
		800 / bright_factor, 600 / bright_factor);




	res = new ResourceLoader();
	res->LoadResourcePaths(AString::char_to_str("map1.AAETHER"));
	res->Add("Environment", new Environment(res->GetEnvFile()));
	res->Add("FilterSettings", new FilterSettings(res->GetFSettingsFile()));
	res->Add("Entities", new SceneInfo(res->GetSceneFile()));
	res->LoadChanges();




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