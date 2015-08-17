#include "entity_manager.hpp"





void EntityManager::Init()
{




}







void EntityManager::RenderPatch(std::vector<EntityInstance*> patch_info)
{




	for (GLuint i = 0; i < patch_info.size(); i++)
		patch_info[i]->Enable(GetManager());



}





void EntityManager::RenderQuad(QuadNode * node)
{
	


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	MeshShader * shader = static_cast<MeshShader*>(GetManager()->Get("Pipeline")->Get("MeshWrapper"));



	QuadTree * tree = dm->GetTree();
	ResourceLoader * res = static_cast<ResourceLoader*>(dm->Get("Resources"));
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));





	GLuint result = Math::SphereInFrustum(camera->GetFrustum(), node->GetCenter(), node->GetRadius() + 12.5);


	if (!result)
		return;


	if (node->GetNodes())
	{
		for (GLuint i = 0; i < 4; i++)
			this->RenderQuad(node->GetNodes()[i]);
	}
	else
	this->RenderPatch(scene_info->GetEntityInstances()[node->GetInd()]);



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





