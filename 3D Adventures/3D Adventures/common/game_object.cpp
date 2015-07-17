#include "game_object.hpp"



void GameObject::Init(GLuint window_width, GLuint window_height)
{


	this->shadow_bbox = new ShadowBBox();


	GLuint dof_factor = 2;
	GLuint bright_factor = 2;
	this->techniques = new Techniques();
	this->techniques->Create(window_width, window_height, ShadowMapWidth, ShadowMapHeight,
		window_width / dof_factor, window_height / dof_factor,
		window_width / bright_factor, window_height / bright_factor);



	this->res = new ResourceLoader();




}




void GameObject::Clean()
{


	delete this->shadow_bbox;
	delete this->res;
	delete this->techniques;


}




GLuint GameObject::GetInd(glm::vec3 pos)
{


	if (q_tree)
		return GLuint(pos.z / q_tree->GetMinZ())*q_tree->GetWidth() +
		GLuint(pos.x / q_tree->GetMinX());


}