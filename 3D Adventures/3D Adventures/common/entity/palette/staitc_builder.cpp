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
















void StaticPalette::Init()
{


	this->builder = new StaticBuilder();
	ui_scene = new ui_Scene();
	ui_transform = new ui_Transform();



	visible = false;
	id = 0;
	number_of_entities = 0;



}



void StaticPalette::SetNumbers(GLuint e_n)
{



	number_of_entities = e_n - 1;
	id = 0;




}



glm::mat4 StaticPalette::GetMatrix(GLboolean model_type, GLuint special){



	//make sure we're using the same model coords
	
	
	glm::mat3 trans = ui_transform->GetPInfo()->trans;
	glm::mat4 model_matrix;



	if (model_type == AAETHER_MODEL)
		model_matrix = Math::Translation(trans[0])*
		Math::Rotate(trans[1])*
		Math::Scale(trans[2]);
	else if (model_type == GRANNY_MODEL)
		model_matrix = Math::Translation(trans[0])*
		Math::Rotate(trans[1] + glm::vec3(-M_PI / 2.0f, 0.0, 0.0f))*
		Math::Scale(trans[2] / 100.0f);


	return model_matrix;

}







void StaticPalette::Render(Controller*ctrl, MeshShader *u_data, StaticEntity ** entity)
{


	//rendering entity depending on the palette id


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
	if (id < number_of_entities && ctrl->GetKeyOnce(GLFW_KEY_E))
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
			entity_info[ui_scene->GetSelectedData()[i].x].erase(entity_info[ui_scene->GetSelectedData()[i].x].begin() + ui_scene->GetSelectedData()[i].y);
			ui_scene->UpdateSceneData(ui_scene->GetSelectedData()[i].x, ui_scene->GetSelectedData()[i].y);

		}

			ui_scene->ClearSelectedDataFromScene();


	}






}



void StaticPalette::PlacePalette(Controller * ctrl, std::vector<StaticEntityInfo*>*entity_info, StaticEntity **entity)
{




	//placing the palette entity


	if (ctrl->GetKeyOnce(GLFW_KEY_SPACE) && visible)
	{



		visible = false;
		StaticEntityInfo *temp = new StaticEntityInfo();


		temp->SetId(id);
		temp->SetMatrix(GetMatrix(entity[id]->GetType(), id));


		GLuint ind = ctrl->GetGameObject()->GetInd(ctrl->GetCameraPointer()->GetInfo()->getCameraPos());


		ui_scene->AddItem(std::to_string(id), glm::ivec2(ind, entity_info[ind].size()));
		entity_info[ind].push_back(temp);




	}

}











