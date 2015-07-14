#ifndef UNIFORM_HPP
#define UNIFORM_HPP




#include <shader/shader.hpp>
#include <util/controller_math.hpp>
#include <granny.h>




#ifndef MAX_BONES
#define MAX_BONES 128
#endif





class MeshShader : public Shader
{


public:


	inline MeshShader() : Shader(){ this->Init(); }
	void Init();


	void Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 NormalMatrix);
	inline void Space(glm::mat4 ModelMatrix, View * view){ Space(ModelMatrix, view->getViewMatrix(), view->getProjectionMatrix(), glm::transpose(glm::inverse(view->getViewMatrix() * ModelMatrix))); }



	inline void SetGrannyBoneTransform(GLuint numBones, granny_matrix_4x4 GrannyBones[MAX_BONES])
	{ 
		Set("Bones[0]", GrannyBones, numBones); 
	}


	inline void SetSpecular(GLfloat specular_intensity, GLfloat specular_power)
	{
		Set("specular_intensity", specular_intensity);
		Set("specular_power", specular_power);
	}




};







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








