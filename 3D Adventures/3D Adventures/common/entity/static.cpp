#include "static.hpp"





void StaticManager::Init(Controller *ctrl)
{


	QuadTree * tree = ctrl->GetGameObject()->GetTree();
	quad_width = tree->GetWidth();
    quad_height = tree->GetHeight();

	
	palette = new StaticPalette();


}







void StaticManager::Load(char*path, Controller * ctrl)
{
	


	QuadTree * tree = ctrl->GetGameObject()->GetTree();




	GLuint size, temp_ind,temp_id;
	glm::mat4 temp_matrix;
	std::vector<char> temp_str;



	GLuint quad_width, quad_height;
	std::ifstream fin(path, std::ios::binary);



	fin.read((char*)&(quad_width), sizeof(GLuint));
	fin.read((char*)&(quad_height), sizeof(GLuint));

	
	
	quad_width = quad_height = 8;
	assert(quad_width == tree->GetWidth() && quad_height == tree->GetHeight());

	

	fin.read((char*)&(this->e_n), sizeof(GLuint));


	if (this->e_n)

	{



		this->entity = new StaticEntity*[e_n];
		this->entity_info = new std::vector<StaticEntityInfo*>[tree->GetWidth()*tree->GetHeight()];



		for (GLuint i = 0; i < e_n; i++)
		{


			this->entity[i] = new StaticEntity();


			fin.read((char*)&(size), sizeof(GLuint));
			this->entity[i]->SetType(size);


			fin.read((char*)&(size), sizeof(GLuint));
			temp_str.resize(size);
			fin.read((char*)&(temp_str[0]), sizeof(char)*size);
			temp_str.push_back('\0');


			this->entity[i]->SetPath(&temp_str[0]);


			if (this->entity[i]->GetType() == GRANNY_MODEL)
			{



				this->entity[i]->SetGranny(new GrannyModel);
				this->entity[i]->GetGranny()->Load(&temp_str[0]);



			}
			else if (this->entity[i]->GetType() == AAETHER_MODEL)
			{


				this->entity[i]->SetAaether(new Aa_model());
				this->entity[i]->GetAaether()->Load(&temp_str[0]);


			}




		}



		
		do
		{


			fin.read((char*)&(size), sizeof(GLuint));


			if (size == -1)break;

			fin.read((char*)&(temp_ind), sizeof(GLuint));

			for (GLuint i = 0; i < size; i++)
			{


				StaticEntityInfo*temp_info = new StaticEntityInfo();
				

				fin.read((char*)&(temp_id), sizeof(GLuint));
				fin.read((char*)&(temp_matrix), sizeof(glm::mat4));
				temp_info->SetId(temp_id);
				temp_info->SetMatrix(temp_matrix);


				entity_info[temp_ind].push_back(temp_info);
				


			}


		} while (size != -1);
		
		


	}


	fin.close();



	palette->SetNumbers(this->e_n);
	palette->SetDataPointers(this->entity, this->entity_info);
	palette->SetWidth(tree->GetWidth());
	palette->SetHeight(tree->GetHeight());


}






void StaticManager::RenderPatch(Controller*ctrl, MeshShader *shader, std::vector<StaticEntityInfo*> patch_info)
{



	for (GLuint i = 0; i < patch_info.size(); i++)
		patch_info[i]->Render(ctrl, shader, this->entity);




}





void StaticManager::RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node)
{


	GLuint result = Math::SphereInFrustum(ctrl->GetCameraPointer()->GetFrustum(), node->GetCenter(), node->GetRadius() + 12.5);


	if (!result)
		return;


	if (node->GetNodes())
	{
		for (GLuint i = 0; i < 4; i++)
			this->RenderQuad(ctrl, shader, node->GetNodes()[i]);
	}
	else
	this->RenderPatch(ctrl, shader, this->entity_info[node->GetInd()]);



}




void StaticManager::Render(Controller *ctrl, MeshShader *shader)
{


	QuadTree * tree = ctrl->GetGameObject()->GetTree();


	this->RenderQuad(ctrl, shader,tree->GetStartNode());


}







void StaticManager::Clean()
{


	delete this->entity;


	for (GLuint i = 0; i < this->quad_width * this->quad_height; i++)
	destroy_vector(this->entity_info[i]);

}





