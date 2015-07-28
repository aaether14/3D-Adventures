#include "entity_palette.hpp"







void EntityPalette::Init()
{


	ui_scene_outliner = new ui_SceneOutliner();
	ui_transform_tab = new ui_TransformTab();



	visible = false;
	entity_counter = 0;


}



void EntityPalette::Clean()
{


	delete ui_scene_outliner;
	delete ui_transform_tab;

}




glm::mat4 EntityPalette::GetMatrix(Entity *entity)
{


	InfoComponent * ic = static_cast<InfoComponent*>(entity->GetComponent("InfoComponent"));


	//make sure we're using the same model coords
	
	
	glm::mat3 trans = ui_transform_tab->GetPInfo()->trans;
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







void EntityPalette::Enable()
{


	//rendering entity depending on the palette id


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));
	MeshShader * shader = static_cast<MeshShader*>((GetManager()->Get("Pipeline"))->Get("MeshWrapper"));


	ResourceLoader * res = dm->GetResource();
	Techniques * tech = dm->GetTechniques();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));
	View * view = camera->GetView();
	ViewInfo *info = camera->GetInfo();



	if (visible)
		current_entity->Render(info, view, res, tech, shader, GetMatrix(current_entity));



}


void EntityPalette::ManagePaletteInput()
{



	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));



	ResourceLoader * res = dm->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));



	//applying transform & making visible


	if (ctrl->GetKey(GLFW_KEY_LEFT_ALT))
	{
		ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
		ui_transform_tab->UpdateData();
		visible = true;
	}



	//switching trough the palette


	if (entity_counter > 0 && ctrl->GetKeyOnce(GLFW_KEY_Q))
	{
		entity_counter--;
		ui_transform_tab->GetPInfo()->Reset();
		ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
		ui_transform_tab->UpdateData();
	}
	if (entity_counter < scene_info->GetNumberOfEntities() - 1 && ctrl->GetKeyOnce(GLFW_KEY_E))
	{
		entity_counter++;
		ui_transform_tab->GetPInfo()->Reset();
		ui_transform_tab->GetPInfo()->trans[0] = camera->GetInfo()->getCameraPos();
		ui_transform_tab->UpdateData();
	}


	current_entity = scene_info->GetEntity(entity_counter);



	//erase entities from scene



	if (ctrl->GetKeyOnce(GLFW_KEY_DELETE))
	{



		for (GLuint i = 0; i < ui_scene_outliner->GetSelectedData().size(); i++)
		{
			scene_info->GetEntityInfos()[ui_scene_outliner->GetSelectedData()[i].x].erase(
				scene_info->GetEntityInfos()[ui_scene_outliner->GetSelectedData()[i].x].begin() + ui_scene_outliner->GetSelectedData()[i].y);
			ui_scene_outliner->UpdateSceneData(ui_scene_outliner->GetSelectedData()[i].x, ui_scene_outliner->GetSelectedData()[i].y);

		}

			ui_scene_outliner->ClearSelectedDataFromScene();


	}






}



void EntityPalette::ManageEntityPlacing()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


	ResourceLoader * res = dm->GetResource();
	SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));
	Camera * camera = static_cast<Camera*>(ctrl->Get("Camera"));


	InfoComponent * ic = static_cast<InfoComponent*>(current_entity->GetComponent("InfoComponent"));


	//placing the palette entity


	if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
	{



		visible = false;
		TransformInfo *new_instance = new TransformInfo();



		new_instance->entity_name = ic->GetInfo()->entity_name;
		new_instance->matrix = GetMatrix(current_entity);
		new_instance->pos = ui_transform_tab->GetPInfo()->trans[0];
		new_instance->rot = ui_transform_tab->GetPInfo()->trans[1];
		new_instance->scale = ui_transform_tab->GetPInfo()->trans[2];


		if (ic)
		{
			new_instance->rot += ic->GetInfo()->base_rot;
			new_instance->scale *= ic->GetInfo()->base_scale;
		}


		GLuint ind = static_cast<DataManager*>(ctrl->Get("DataManager"))->GetInd(camera->GetInfo()->getCameraPos());


		ui_scene_outliner->AddItem(ic->GetInfo()->entity_name, glm::ivec2(ind, scene_info->GetEntityInfos()[ind].size()));
		scene_info->GetEntityInfos()[ind].push_back(new_instance);




	}

}











