#include "skybox.hpp"





Skybox::Skybox()
{
	this->Init();
}




Skybox::~Skybox()
{
	this->Clean();
}




void Skybox::Init(){


	this->sky_shader = new Shader();
	this->sky_shader->Add("data/shaders/skybox_vert.txt", GL_VERTEX_SHADER);
	this->sky_shader->Add("data/shaders/skybox_frag.txt", GL_FRAGMENT_SHADER);
	this->sky_shader->Link();


	this->sky_shader->AddVariable("MVP");
	this->sky_shader->AddVariable("MV");
	this->sky_shader->AddVariable("cube");
	this->sky_shader->AddVariable("fog_color");


	this->sky_render = new SkyRender();


	this->sky_render->LoadCube("data/objects/sphere/dusk/",
		"px.jpg",
		"nx.jpg",
		"py.jpg",
		"ny.jpg",
		"pz.jpg",
		"nz.jpg");



}

void Skybox::Clean()
{


	delete this->sky_shader;
	delete this->sky_render;


}



void Skybox::SetUniforms(Controller * ctrl, glm::mat4 MVP, glm::mat4 MV)
{


	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));



	this->sky_shader->Set("cube", 0);
	this->sky_shader->Set("MVP", MVP);
	this->sky_shader->Set("MV", MV);



	glm::vec4 f = glm::vec4(env->fog_color, 1.0);
	this->sky_shader->Set("fog_color", f);



}





void Skybox::Render(Controller * ctrl, glm::mat4 MVP, glm::mat4 MV)
{
	

	this->sky_shader->Use();
	this->SetUniforms(ctrl, MVP, MV);
	this->sky_render->Render(ctrl);
	this->sky_shader->Stop();



}