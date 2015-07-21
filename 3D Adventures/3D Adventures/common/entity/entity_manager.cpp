#include "entity_manager.hpp"





void EntityManager::Init(Controller *ctrl)
{


	palette = new EntityPalette();


}









void EntityManager::RenderPatch(Controller*ctrl, MeshShader *shader, std::vector<TransformInfo*> patch_info)
{


	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo *info = ctrl->GetCameraPointer()->GetInfo();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


	for (GLuint i = 0; i < patch_info.size(); i++)
		patch_info[i]->Render(info, view, res, tech, shader, scene_info->GetEntity(patch_info[i]->entity_name));




}





void EntityManager::RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node)
{



	QuadTree * tree = ctrl->GetGameObject()->GetTree();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));




	if (scene_info->ShouldReset())
	{
		for (GLuint i = 0; i < tree->GetWidth() * tree->GetHeight(); i++)
			for (GLuint j = 0; j < scene_info->GetEntityInfos()[i].size(); j++)
				palette->GetSceneOutliner()->AddItem(scene_info->GetEntityInfos()[i][j]->entity_name,
				glm::ivec2(i, j));

		scene_info->SetShouldReset(false);
	}





	GLuint result = Math::SphereInFrustum(ctrl->GetCameraPointer()->GetFrustum(), node->GetCenter(), node->GetRadius() + 12.5);


	if (!result)
		return;


	if (node->GetNodes())
	{
		for (GLuint i = 0; i < 4; i++)
			this->RenderQuad(ctrl, shader, node->GetNodes()[i]);
	}
	else
	this->RenderPatch(ctrl, shader, scene_info->GetEntityInfos()[node->GetInd()]);



}




void EntityManager::Render(Controller *ctrl, MeshShader *shader)
{


	QuadTree * tree = ctrl->GetGameObject()->GetTree();
	this->RenderQuad(ctrl, shader,tree->GetStartNode());


}







void EntityManager::Clean()
{


	if (palette)
	delete palette;


}





