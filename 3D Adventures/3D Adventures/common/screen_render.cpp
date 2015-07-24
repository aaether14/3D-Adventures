#include "screen_render.hpp"



void ScreenRender::Init()

{


	shader2d = new Shader();
	shader2d->Add("data/shaders/2d_vert.txt", GL_VERTEX_SHADER);
	shader2d->Add("data/shaders/2d_frag.txt", GL_FRAGMENT_SHADER);
	shader2d->Link();
	
	shader2d->AddVariable("texture");
	shader2d->AddVariable("texture1");
	shader2d->AddVariable("texture2");
	shader2d->AddVariable("use_dof");
	shader2d->AddVariable("white_point");




	this->quad = new Quad();


}




void ScreenRender::Clean()
{

	delete shader2d;
	delete quad;

}




void ScreenRender::Render(GLuint texture,
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




