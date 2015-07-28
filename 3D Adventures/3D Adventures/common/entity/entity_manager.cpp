#include "entity_manager.hpp"





void EntityManager::Init()
{




}







void EntityManager::RenderPatch(std::vector<TransformInfo*> patch_info)
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	MeshShader * shader = static_cast<MeshShader*>(GetManager()->Get("Pipeline")->Get("MeshWrapper"));



	ResourceLoader * res = dm->GetResource();
	Techniques * tech = dm->GetTechniques();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
	View * view = camera->GetView();
	ViewInfo *info = camera->GetInfo();




	for (GLuint i = 0; i < patch_info.size(); i++)
		patch_info[i]->Render(info, view, res, tech, shader, scene_info->GetEntity(patch_info[i]->entity_name));




}





void EntityManager::RenderQuad(QuadNode * node)
{
	


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	MeshShader * shader = static_cast<MeshShader*>(GetManager()->Get("Pipeline")->Get("MeshWrapper"));



	QuadTree * tree = dm->GetTree();
	ResourceLoader * res = dm->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));




	/*
	if (scene_info->ShouldReset())
	{


		palette->GetSceneOutliner()->ClearItems();


		for (GLuint i = 0; i < tree->GetWidth() * tree->GetHeight(); i++)
			for (GLuint j = 0; j < scene_info->GetEntityInfos()[i].size(); j++)
				palette->GetSceneOutliner()->AddItem(scene_info->GetEntityInfos()[i][j]->entity_name,
				glm::ivec2(i, j));

		scene_info->SetShouldReset(false);
	}
	*/




	GLuint result = Math::SphereInFrustum(camera->GetFrustum(), node->GetCenter(), node->GetRadius() + 12.5);


	if (!result)
		return;


	if (node->GetNodes())
	{
		for (GLuint i = 0; i < 4; i++)
			this->RenderQuad(node->GetNodes()[i]);
	}
	else
	this->RenderPatch(scene_info->GetEntityInfos()[node->GetInd()]);



}




void EntityManager::Enable()
{



	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	QuadTree * tree = dm->GetTree();
	RenderQuad(tree->GetStartNode());


}







void EntityManager::Clean()
{





}





