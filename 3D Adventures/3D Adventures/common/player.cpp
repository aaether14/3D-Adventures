#include "player.hpp"


void Player::SaveChar(char *path)
{


	glm::mat4 cache = Math::Translation(0, 0.38, 0)*
		Math::Scale(0.01, 0.01, 0.01)*
		Math::Rotate(0, 0, -M_PI / 2);

	std::string *files = new std::string[3];


	files[0] = "data/character/fighter/diablo2.gr2";
	files[1] = "data/character/fighter/horse/wait.gr2";
	files[2] = "data/character/fighter/horse/run.gr2";


	this->WriteCharCache(path, files, 3, cache, NO_HELMET);



}



void Player::SaveMount(char* path)
{


	glm::mat4 cache = Math::Rotate(0, M_PI, M_PI / 2)*
		Math::Translation(0, -38, -110);

	std::string *files = new std::string[3];


	files[0] ="data/npc/lion/lion.gr2";
	files[1] = "data/npc/lion/wait.gr2";
	files[2] = "data/npc/lion/run.gr2";



	this->WriteMountCache(path, files, 3, cache);

}




void Player::SaveWeap(char *path)

{



	std::string*files = new std::string[2];

	files[0] = "data/weapon/onehanded/gold.gr2";
	files[1] = "equip_right_hand";

	this->WriteWeapCache(path, files);


}







void Player::WriteCharCache(char *path, std::string*files, GLuint n, glm::mat4 cache, GLuint type)
{


	
	std::ofstream  os(path, std::ios::binary);

	os.write((const char*)&(n), sizeof(GLuint));

	for (GLuint i = 0; i < n; i++){
		GLuint size = files[i].length();
		os.write((const char*)&(size), sizeof(GLuint));
		os.write((const char*)&(files[i][0]), sizeof(char)*size);
	}

	os.write((const char*)&(cache[0][0]), sizeof(glm::mat4));
	os.write((const char*)&(type), sizeof(GLuint));


	os.close();




}



void Player::LoadChar(char *path)
{


	this->cube = new Aa_model();
	this->cube->Load("data/objects/cube/cube.aao");



	this->anim = 0;
	this->angle = -M_PI / 2;


	GLuint n, size;
	std::vector<char> temp;

	this->player_model = new GrannyModel();


	std::ifstream is(path, std::ios::binary);


	is.read((char*)&(n), sizeof(GLuint));



		is.read((char*)&(size), sizeof(GLuint));
		temp.resize(size);
		is.read(&temp[0], sizeof(char)*size);
		temp.push_back('\0');

		this->player_model->Load(&temp[0]);


		for (GLuint i = 1; i < n; i++)
		{


			is.read((char*)&(size), sizeof(GLuint));
			temp.resize(size);
			is.read(&temp[0], sizeof(char)*size);
			temp.push_back('\0');

			this->player_model->LoadAnimation(&temp[0]);


		}




		is.read((char*)&(this->player_cache[0][0]), sizeof(glm::mat4));
		is.read((char*)&(this->type), sizeof(GLuint));



	is.close();



}


void Player::WriteWeapCache(char *path, std::string*files)
{

	std::ofstream os(path, std::ios::binary);

	GLuint size = files[0].length();
	os.write((const char*)&(size), sizeof(GLuint));
	os.write((const char*)&(files[0][0]), sizeof(char)*size);

	size = files[1].length();
	os.write((const char*)&(size), sizeof(GLuint));
	os.write((const char*)&(files[1][0]), sizeof(char)*size);


	os.close();

}



void Player::LoadMount(char *path)
{


	GLuint n, size;
	std::vector<char> temp;

	this->mount_model = new GrannyModel();


	std::ifstream is(path, std::ios::binary);


	is.read((char*)&(n), sizeof(GLuint));



	is.read((char*)&(size), sizeof(GLuint));
	temp.resize(size);
	is.read(&temp[0], sizeof(char)*size);
	temp.push_back('\0');

	this->mount_model->Load(&temp[0]);


	for (GLuint i = 1; i < n; i++)
	{


		is.read((char*)&(size), sizeof(GLuint));
		temp.resize(size);
		is.read(&temp[0], sizeof(char)*size);
		temp.push_back('\0');

		this->mount_model->LoadAnimation(&temp[0]);


	}




	is.read((char*)&(this->mount_cache[0][0]), sizeof(glm::mat4));



	is.close();


}


void Player::LoadWeap(char *path)
{


	this->weapon = new GrannyModel();



	GLuint size;
	std::vector<char> temp;


	std::ifstream is(path, std::ios::binary);


	is.read((char*)&(size), sizeof(GLuint));
	temp.resize(size);
	is.read(&temp[0], sizeof(char)*size);
	temp.push_back('\0');


	this->weapon->Load(&temp[0]);


	is.read((char*)&(size), sizeof(GLuint));
	temp.resize(size);
	is.read(&temp[0], sizeof(char)*size);
	temp.push_back('\0');

	this->player_model->AttachGrannyModel(this->weapon, &temp[0]);



	is.close();


}


void Player::WriteMountCache(char *path, std::string*files, GLuint n, glm::mat4 cache)
{



	std::ofstream  os(path, std::ios::binary);

	os.write((const char*)&(n), sizeof(GLuint));

	for (GLuint i = 0; i < n; i++){
		GLuint size = files[i].length();
		os.write((const char*)&(size), sizeof(GLuint));
		os.write((const char*)&(files[i][0]), sizeof(char)*size);
	}

	os.write((const char*)&(cache[0][0]), sizeof(glm::mat4));


	os.close();


}



void Player::Enable(Controller *ctrl)

{




	if (ctrl->GetKey(GLFW_KEY_W))
		this->anim = 1;
	else
		this->anim = 0;


	if (ctrl->GetKey(GLFW_KEY_W))
		this->angle = ctrl->GetCameraPointer()->getHorizontalAngle() + M_PI / 2;



	this->player_matrix = 
		Math::Translation(ctrl->GetCameraPointer()->GetInfo()->getCameraPos())*
		this->player_cache*
		Math::Rotate(0, 0, angle);

	this->weapon_matrix = player_matrix * Math::ConvertGrannyMatrix(this->player_model->GiveTransform()[128]);

    
	this->mount_matrix = player_matrix * mount_cache;

}




void Player::RenderCube(Controller *ctrl, MeshShader *shader)
{


	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();



	shader->Space(
		Math::Translation(info->getCameraPos())*
		Math::Rotate(0, angle, 0)*
		Math::Scale(1.5f, 0.1f, 0.75f),
		view);



	cube->Render();


}




void Player::Render(Controller *ctrl, MeshShader * shader)
{


	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));



	glm::mat4 orth = tech->GetShadow()->GetDirectionalShadow(env, info);


	//Mount--------------------



	if (tech->GetSSAO()->OnGeometryPass())
	{

		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * this->mount_matrix,
			view->getViewMatrix() * this->mount_matrix);
		tech->GetSSAO()->SetGrannyBoneTransform(this->mount_model->GetNumBones(), this->mount_model->GiveTransform());


	}
	if (tech->GetShadow()->OnShadowPass())
	{

		tech->GetShadow()->UniformMVP(orth*this->mount_matrix);
		tech->GetShadow()->SetGrannyBoneTransform(this->mount_model->GetNumBones(), this->mount_model->GiveTransform());

	}
	else
	{


		shader->Space(mount_matrix, view);



		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);




		shader->Set("LightMatrix", biasMatrix*
			tech->GetShadow()->GetDirectionalShadow(env, info)*this->mount_matrix);



		shader->SetGrannyBoneTransform(mount_model->GetNumBones(), mount_model->GiveTransform());
		this->mount_model->PlayAnimation(this->anim, 0);


	}
	


	this->mount_model->Render(this->anim);




	//Player-------------------


	shader->SetSpecular(32.0, 64.0f);



	if (tech->GetSSAO()->OnGeometryPass())
	{


		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * this->player_matrix,
			view->getViewMatrix() * this->player_matrix);
		tech->GetSSAO()->SetGrannyBoneTransform(this->player_model->GetNumBones(), this->player_model->GiveTransform());


	}
	else if (tech->GetShadow()->OnShadowPass())
	{


		tech->GetShadow()->UniformMVP(orth*this->player_matrix);
		tech->GetShadow()->SetGrannyBoneTransform(this->player_model->GetNumBones(), this->player_model->GiveTransform());


	}
	else
	{



		shader->Space(player_matrix, view);



		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);




		shader->Set("LightMatrix", biasMatrix*
			tech->GetShadow()->GetDirectionalShadow(env, info)*player_matrix);


		shader->SetGrannyBoneTransform(this->player_model->GetNumBones(), this->player_model->GiveTransform());
		this->player_model->PlayAnimation(this->anim, 0);


	}


	this->player_model->Render(this->anim);




	//Weapon----------------------


	
	shader->SetSpecular(32.0, 64.0f);



	if (tech->GetSSAO()->OnGeometryPass())
	{


		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * this->weapon_matrix,
			view->getViewMatrix() * this->weapon_matrix);

	}
	else if (tech->GetShadow()->OnShadowPass())
	{


		tech->GetShadow()->UniformMVP(orth*this->weapon_matrix);


	}
	else
	{


		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);




		shader->Set("LightMatrix", biasMatrix*
			tech->GetShadow()->GetDirectionalShadow(env, info)*weapon_matrix);



		shader->Space(weapon_matrix, view);


	}


	this->player_model->RenderAttachedModel(this->weapon);
	this->weapon->Render(-1);


	shader->SetSpecular(0.0f, 1.0f);





}



void Player::Clean()
{



	if (player_model)
		delete player_model;


	if (mount_model)
		delete mount_model;

	if (weapon)
		delete weapon;


	if (helmet)
		delete helmet;


}














