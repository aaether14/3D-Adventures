#include "entity_palette.hpp"







void EntityPalette::Init()
{


	ui_scene = new ui_Scene();
	ui_transform = new ui_Transform();



	visible = false;
	entity_counter = 0;


}




glm::mat4 EntityPalette::GetMatrix(Entity *entity)
{


	InfoComponent * ic = static_cast<InfoComponent*>(entity->GetComponent("InfoComponent"));


	//make sure we're using the same model coords
	
	
	glm::mat3 trans = ui_transform->GetPInfo()->trans;
	glm::mat4 model_matrix;


	if (ic)
	{
		trans[1] += ic->GetInfo()->base_rot;
		trans[2] *= ic->GetInfo()->base_scale;
	}


	model_matrix = Math::Translation(trans[0])*
	Math::Rotate(trans[1])*
    Math::Scale(trans[2]);


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
		current_entity->Render(info, view, res, tech, u_data, GetMatrix(current_entity));



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


	if (entity_counter > 0 && ctrl->GetKeyOnce(GLFW_KEY_Q))
	{
		entity_counter--;
		ui_transform->GetPInfo()->Reset();
		ui_transform->GetPInfo()->trans[0] = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		ui_transform->UpdateData();
	}
	if (entity_counter < scene_info->GetNumberOfEntities() - 1 && ctrl->GetKeyOnce(GLFW_KEY_E))
	{
		entity_counter++;
		ui_transform->GetPInfo()->Reset();
		ui_transform->GetPInfo()->trans[0] = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		ui_transform->UpdateData();
	}


	current_entity = scene_info->GetEntity(entity_counter);



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
	InfoComponent * ic = static_cast<InfoComponent*>(current_entity->GetComponent("InfoComponent"));


	//placing the palette entity


	if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
	{



		visible = false;
		TransformInfo *new_instance = new TransformInfo();



		new_instance->entity_name = ic->GetInfo()->name;
		new_instance->matrix = GetMatrix(current_entity);
		new_instance->pos = ui_transform->GetPInfo()->trans[0];
		new_instance->rot = ui_transform->GetPInfo()->trans[1];
		new_instance->scale = ui_transform->GetPInfo()->trans[2];


		if (ic)
		{
			new_instance->rot += ic->GetInfo()->base_rot;
			new_instance->scale *= ic->GetInfo()->base_scale;
		}


		GLuint ind = ctrl->GetGameObject()->GetInd(ctrl->GetCameraPointer()->GetInfo()->getCameraPos());


		ui_scene->AddItem(ic->GetInfo()->name, glm::ivec2(ind, scene_info->GetEntityInfos()[ind].size()));
		scene_info->GetEntityInfos()[ind].push_back(new_instance);




	}

}











