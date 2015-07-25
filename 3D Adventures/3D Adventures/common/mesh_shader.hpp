#ifndef MESH_SHADER_HPP
#define MESH_SHADER_HPP




#include <shader/shader.hpp>
#include <util/math_helper.hpp>
#include <light/light.hpp>
#include <granny.h>




#ifndef MAX_BONES
#define MAX_BONES 128
#endif






class MeshShader : public Shader
{


	Light *m_light;


public:


	inline MeshShader() : Shader(){ Init(); }
	void Init();
	inline ~MeshShader() { Clean(); }
	void Clean();


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


	inline Light * GetLight(){ return m_light; }




};









#endif








