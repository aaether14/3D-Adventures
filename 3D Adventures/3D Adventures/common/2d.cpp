#include "2d.hpp"



void Aaether2D::Init()

{


	this->shader2d = new Shader();
	this->shader2d->Add("data/shaders/2d_vert.txt", GL_VERTEX_SHADER);
	this->shader2d->Add("data/shaders/2d_frag.txt", GL_FRAGMENT_SHADER);
	this->shader2d->Link();
	
	this->shader2d->AddVariable("texture");
	this->shader2d->AddVariable("texture1");
	this->shader2d->AddVariable("texture2");
	this->shader2d->AddVariable("use_dof");
	this->shader2d->AddVariable("white_point");




	this->quad = new Quad();


}




void Aaether2D::Clean()
{

	delete shader2d;
	delete quad;

}




void Aaether2D::Render(GLuint texture,
	GLuint texture1,
	GLuint texture2,
	GLfloat use_dof,
	GLfloat white_point,
	glm::ivec2 window_size)
{



	glViewport(0, 0, window_size.x, window_size.y);
	this->shader2d->Use();


	this->shader2d->Set("use_dof", use_dof);
	this->shader2d->Set("white_point", white_point);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	this->shader2d->Set("texture", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	this->shader2d->Set("texture1", 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	this->shader2d->Set("texture2", 2);


	this->quad->Render();
	this->shader2d->Stop();


}




