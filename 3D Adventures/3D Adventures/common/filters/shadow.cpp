#include "shadow.hpp"



void ShadowImplementation::Init(GLuint width, GLuint height)
{


	this->width = width;
	this->height = height;
	this->shadow_size = 80.0f;


	this->shadow_shader = new Shader();
	this->shadow_shader->Add("data/shaders/shadow_vert.txt", GL_VERTEX_SHADER);
	this->shadow_shader->Add("data/shaders/shadow_frag.txt", GL_FRAGMENT_SHADER);
	this->shadow_shader->Link();


	this->shadow_shader->AddVariable("depthMVP");
	this->shadow_shader->AddVariable("Bones[0]");



	this->shadow_map = new TextureObject(1);
	this->shadow_map->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_R32F, GL_RGBA,
		GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_BORDER);
	this->temp_shadow_map = new TextureObject(1);
	this->temp_shadow_map->CreateTexture(COLOR_TYPE, GL_TEXTURE_2D, width, height, GL_R32F, GL_RGBA,
		GL_FLOAT, 0, GL_LINEAR, GL_CLAMP_TO_BORDER);



}



void ShadowImplementation::Clean()
{

	if (shadow_shader)
	delete shadow_shader;

	if (shadow_map)
	delete shadow_map;


	if (temp_shadow_map)
	delete temp_shadow_map;


}




glm::mat4 ShadowImplementation::GetDirectionalShadow(Environment * env, ViewInfo * info)
{

	glm::vec3 position = info->getCameraPos();
	glm::vec3 direction = info->getDirection();

	glm::vec3 shadow_pos = position + direction*(shadow_size / 2.0f);
	GLfloat texel_size = shadow_size * 2.0 / GLfloat(width);


	shadow_pos = glm::mat3(glm::lookAt(position, position + env->sun_dir, glm::vec3(0, 1, 0))) * shadow_pos;
	shadow_pos.x = glm::floor(shadow_pos.x / texel_size) * texel_size;
	shadow_pos.y = glm::floor(shadow_pos.y / texel_size) * texel_size;
	shadow_pos = glm::inverse(glm::mat3(glm::lookAt(position, position + env->sun_dir, glm::vec3(0, 1, 0)))) * shadow_pos;


	return glm::ortho<float>(-shadow_size, shadow_size, -shadow_size, shadow_size, shadow_size, -shadow_size)*
		glm::lookAt(shadow_pos, shadow_pos + env->sun_dir, glm::vec3(0, 1, 0));

}