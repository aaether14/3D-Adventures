#ifndef TERRAIN_SHADER_HPP
#define TERRAIN_SHADER_HPP





#include <shader/shader.hpp>
#include <util/controller_math.hpp>





class TerrainShader : public Shader
{


public:



	void Init();
	inline TerrainShader() : Shader(){ this->Init(); }



	class TextureAttributes
	{

	public:

		GLfloat diffuse_scale;
		GLfloat detail_scale;
		GLfloat diffuse_intensity;

	};


	void Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);
	inline void Space(glm::mat4 ModelMatrix, View * view){ Space(ModelMatrix, view->getViewMatrix(), view->getProjectionMatrix()); }
	void SendTextureAttributes(TextureAttributes*tex_attributes, GLuint n);

};




void LoadTextureAttributesSet(char * path, TerrainShader::TextureAttributes*tex_data);








#endif