#include "entity_palette.hpp"







void EntityPalette::Init()
{


	ui_scene = new ui_Scene();
	ui_transform = new ui_Transform();



	visible = false;
	id = 0;



}




glm::mat4 EntityPalette::GetMatrix(){



	//make sure we're using the same model coords
	
	
	glm::mat3 trans = ui_transform->GetPInfo()->trans;
	glm::mat4 model_matrix;


	model_matrix = Math::Translation(trans[0])*
	Math::Rotate(trans[1] + glm::vec3(-M_PI / 2.0f, 0.0, 0.0f))*
    Math::Scale(trans[2] / 100.0f);


	return model_matrix;

}







void EntityPalette::Render(Controller*ctrl, MeshShader *u_data)
{


	//rendering entity depending on the palette id




	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo *info = ctrl->GetCameraPointer()->GetInfo();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));



	if (visible)
		scene_info->GetEntities()[id]->Render(info, view, res, tech, u_data, GetMatrix());



}


void EntityPalette::ControlPalette(Controller * ctrl)
{


	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


	//applying transform & making visible


	if (ctrl->GetKey(GLFW_KEY_LEFT_ALT))
	{
		ui_transform->GetPInfo()->trans[0] = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		ui_transform->UpdateData();
		visible = true;
	}



	//switching trough the palette


	if (id > 0 && ctrl->GetKeyOnce(GLFW_KEY_Q))
	{
		id--;
		ui_transform->GetPInfo()->Reset();
		ui_transform->GetPInfo()->trans[0] = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		ui_transform->UpdateData();
	}
	if (id < scene_info->GetEntities().size() && ctrl->GetKeyOnce(GLFW_KEY_E))
	{
		id++;
		ui_transform->GetPInfo()->Reset();
		ui_transform->GetPInfo()->trans[0] = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		ui_transform->UpdateData();
	}






	//erase entities from scene



	if (ctrl->GetKeyOnce(GLFW_KEY_DELETE))
	{



		for (GLuint i = 0; i < ui_scene->GetSelectedData().size(); i++)
		{
			scene_info->GetEntityInfos()[ui_scene->GetSelectedData()[i].x].erase(
				scene_info->GetEntityInfos()[ui_scene->GetSelectedData()[i].x].begin() + ui_scene->GetSelectedData()[i].y);
			ui_scene->UpdateSceneData(ui_scene->GetSelectedData()[i].x, ui_scene->GetSelectedData()[i].y);

		}

			ui_scene->ClearSelectedDataFromScene();


	}






}



void EntityPalette::PlacePalette(Controller * ctrl)
{



	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


	//placing the palette entity


	if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
	{



		visible = false;
		StaticEntityInfo *temp = new StaticEntityInfo();


		temp->SetId(id);
		temp->SetMatrix(GetMatrix());


		GLuint ind = ctrl->GetGameObject()->GetInd(ctrl->GetCameraPointer()->GetInfo()->getCameraPos());


		ui_scene->AddItem(std::to_string(id), glm::ivec2(ind, scene_info->GetEntityInfos()[ind].size()));
		scene_info->GetEntityInfos()[ind].push_back(temp);




	}

}











