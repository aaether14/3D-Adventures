#include "static_builder.hpp"






void StaticBuilder::Create(char*path)
{

	GLuint e_n = 0;

	StaticEntity **entity = new StaticEntity*[e_n];



	this->Save(path,
		entity, e_n,
		NULL,
		8, 8);



}



void StaticBuilder::Save(char*path,
	StaticEntity**entity, GLuint e_n,
	std::vector<StaticEntityInfo*>*entity_info,
	GLuint quad_width,
	GLuint quad_height)
{

	GLuint temp;


	glm::mat4 temp_m;


	std::ofstream fout(path, std::ios::binary);


	fout.write((const char*)&(quad_width), sizeof(GLuint));
	fout.write((const char*)&(quad_height), sizeof(GLuint));



	if (entity)
	{

		fout.write((const char*)&(e_n), sizeof(GLuint));

		for (GLuint i = 0; i < e_n; i++)
		{


			temp = entity[i]->GetType();
			fout.write((const char*)&(temp), sizeof(GLuint));

			temp = entity[i]->GetPath().length();
			fout.write((const char*)&(temp), sizeof(GLuint));

			fout.write((const char*)&(entity[i]->GetPath()[0]), sizeof(char)*temp);


		}

		if (entity_info)
		{





			for (GLuint i = 0; i < quad_width*quad_height; i++)
			{
				if (entity_info[i].size() > 0){


					temp = entity_info[i].size();
					fout.write((const char*)&(temp), sizeof(GLuint));


					temp = i;
					fout.write((const char*)&(temp), sizeof(GLuint));


					for (GLuint j = 0; j < entity_info[i].size(); j++)

					{



						temp = entity_info[i][j]->GetId();
						temp_m = entity_info[i][j]->GetMatrix();
						fout.write((const char*)&(temp), sizeof(GLuint));
						fout.write((const char*)&(temp_m), sizeof(glm::mat4));

					}


				}
			}
		}



		temp = -1;
		fout.write((const char*)&(temp), sizeof(GLuint));

	}

	fout.close();





}






bool StaticPalette::SaveEntities(const CEGUI::EventArgs &args)
{




	if (p_info.file_name.length() > 0)
		GetBuilder()->Save(AString::char_to_str(p_info.file_name),
		GetEntity(),
		GetEntityNumber() + 1,
		GetEntityInfo(),
		GetWidth(),
		GetHeight());


	return 1;

}











void StaticPalette::Init()
{


	this->builder = new StaticBuilder();
	/*
	this->bar = TwNewBar("Palette");
	TwDefine(" Palette position='824 0' ");
	TwAddVarRW(this->bar, "switch_entity", TW_TYPE_UINT32, &this->id, " label='Entity#'  min='0' keyIncr=e keyDecr=q ");
	TwAddVarRW(this->bar, "pos_x", TW_TYPE_FLOAT, &this->pos.x, " label='X' step = 0.075");
	TwAddVarRW(this->bar, "pos_y", TW_TYPE_FLOAT, &this->pos.y, " label='Y' step = 0.075");
	TwAddVarRW(this->bar, "pos_z", TW_TYPE_FLOAT, &this->pos.z, " label='Z' step = 0.075");
	TwAddVarRW(this->bar, "pos_z", TW_TYPE_FLOAT, &this->pos.z, " label='Z' step = 0.075");
	TwAddVarRW(this->bar, "scale", TW_TYPE_FLOAT, &this->scale, " label='Scale' step = 0.075 min='0' ");
	TwAddVarRW(this->bar, "scale_range", TW_TYPE_FLOAT, &this->scale_range, " label='Scale Range' step = 0.03 min='0' ");
	TwAddVarRW(this->bar, "y_rot_range", TW_TYPE_FLOAT, &this->y_rot_range, " label='Rotate Range' step = 0.075 min='0' ");
	TwAddVarRW(this->bar, "rot_x", TW_TYPE_FLOAT, &this->x_rot, " label='Rotate X' step = 0.075");
	TwAddVarRW(this->bar, "rot_y", TW_TYPE_FLOAT, &this->y_rot, " label='Rotate Y' step = 0.075");
	TwAddVarRW(this->bar, "rot_z", TW_TYPE_FLOAT, &this->z_rot, " label='Rotate Z' step = 0.075");
	TwAddVarRW(this->bar, "file_name", TW_TYPE_STDSTRING, &this->file_name, "label = 'Filename' ");
	TwAddButton(this->bar, "save", Save, this, " label='Save' ");
	TwAddButton(this->bar, "empty_file", EmptyFile, this, " label='Empty File' ");
	TwAddButton(this->bar, "undo_last_move", UndoLastMove, this, " label='Undo' ");
	*/


	visible = false;


	p_info.file_name = "data/terrain_files/test.st";
	p_info.ind = 0;
	p_info.scale = 1.0f;
	p_info.scale_range = 0.0f;
	p_info.scale_compute = 0.0f;
	p_info.y_rot_range = 0.0f;
	p_info.y_rot_compute = 0.0f;
	p_info.rot = glm::vec3(0.0);
	p_info.pos = glm::vec3(0.0);


	id = 0;
	number_of_entities = 0;


	ui_scene = new ui_Scene();


}



void StaticPalette::SetNumbers(GLuint e_n)
{



	number_of_entities = e_n - 1;
	id = 0;

	//TwSetParam(bar, "switch_entity", "max", TW_PARAM_INT32, 1, &this->e_n);



}



glm::mat4 StaticPalette::GetMatrix(GLboolean model_type, GLuint special){


	GLfloat t_scale = p_info.scale + p_info.scale_compute;
	GLfloat t_rot_y = p_info.rot.y + p_info.y_rot_compute;


	

	if (model_type == AAETHER_MODEL)
		return Math::Translation(p_info.pos)*
		Math::Rotate(p_info.rot.x, p_info.rot.y, p_info.rot.z)*
		Math::Scale(t_scale);
	else if (model_type == GRANNY_MODEL)
		return Math::Translation(p_info.pos)*
		Math::Rotate(p_info.rot.x - M_PI / 2, t_rot_y, p_info.rot.z)*
		Math::Scale(t_scale / 100.0f);

}







void StaticPalette::Render(Controller*ctrl, MeshShader *u_data, StaticEntity ** entity)
{


	if (visible)
	{


		if (id >= 30)
		{


			if (id < 33)glDisable(GL_CULL_FACE);
			entity[id]->Render(ctrl, u_data, GetMatrix(entity[id]->GetType(), id));
			if (id < 33)glEnable(GL_CULL_FACE);



		}
		else
		{
			entity[id]->Render(ctrl, u_data, GetMatrix(entity[id]->GetType(), id));
		}



	}

}


void StaticPalette::ControlPalette(Controller * ctrl)
{



	if (ctrl->GetKey(GLFW_KEY_LEFT_ALT))
	{

		p_info.ind = ctrl->GetGameObject()->GetInd(ctrl->GetCameraPointer()->GetInfo()->getCameraPos());
		p_info.pos = ctrl->GetCameraPointer()->GetInfo()->getCameraPos();
		if (ctrl->GetKeyOnce(GLFW_KEY_LEFT_ALT))
		{
			p_info.scale_compute = Math::randomf(-p_info.scale_range, p_info.scale_range);
			p_info.y_rot_compute = Math::randomf(-p_info.y_rot_range, p_info.y_rot_range);
		}
		visible = true;

	}



	if (id > 0 && ctrl->GetKeyOnce(GLFW_KEY_Q))
		id--;
	if (id < number_of_entities && ctrl->GetKeyOnce(GLFW_KEY_E))
		id++;





	if (ctrl->GetKeyOnce(GLFW_KEY_DELETE))
	{



		for (GLuint i = 0; i < ui_scene->GetSelectedData().size(); i++)
		{
			entity_info[ui_scene->GetSelectedData()[i].x].erase(entity_info[ui_scene->GetSelectedData()[i].x].begin() + ui_scene->GetSelectedData()[i].y);
			ui_scene->UpdateSceneData(ui_scene->GetSelectedData()[i].x, ui_scene->GetSelectedData()[i].y);

		}

			ui_scene->ClearSelectedDataFromScene();


	}




}



void StaticPalette::PlacePalette(Controller * ctrl, std::vector<StaticEntityInfo*>*entity_info, StaticEntity **entity)
{


	if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
	{



		visible = false;

		StaticEntityInfo *temp = new StaticEntityInfo();

		temp->SetId(id);
		temp->SetMatrix(GetMatrix(entity[id]->GetType(), id));



		ui_scene->AddItem(std::to_string(id), glm::ivec2(p_info.ind, entity_info[p_info.ind].size()));
		entity_info[p_info.ind].push_back(temp);




	}

}











