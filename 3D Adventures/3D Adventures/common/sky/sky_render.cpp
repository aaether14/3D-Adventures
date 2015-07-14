#include "sky_render.hpp"
#include <string.h>



SkyRender::SkyRender()
{
	this->Init();
}



void SkyRender::Init()
{
	this->model = new Aa_model();
	this->model->Load("data/objects/sphere/skybox.aao");
}




SkyRender::~SkyRender()
{
	this->Clean();
}




void SkyRender::Clean()
{
	glDeleteTextures(this->m_textures.size(), &this->m_textures[0]);
	delete this->model;
}




void SkyRender::LoadCube(const char *Directory,
	const char *PosXFilename,
	const char *NegXFilename,
	const char *PosYFilename,
	const char *NegYFilename,
	const char *PosZFilename,
	const char *NegZFilename){

	GLuint temp = TextureObject::load_cube_texture(Directory,
		PosXFilename,
		NegXFilename,
		PosYFilename,
		NegYFilename,
		PosZFilename,
		NegZFilename);


	if (temp > 0)
	{
		this->m_textures.push_back(temp);
		printf("%s: %i\n", "Done loading skybox", temp);
	}


}





void SkyRender::Render(Controller * ctrl){


	GLint OldCullFaceMode;
	glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);


	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->m_textures[0]);
	this->model->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	glCullFace(OldCullFaceMode);
	glDepthFunc(OldDepthFuncMode);
}







