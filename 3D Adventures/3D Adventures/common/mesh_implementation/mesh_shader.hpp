#ifndef MESH_SHADER_HPP
#define MESH_SHADER_HPP





#include <shader/shader.hpp>
#include <util/math_helper.hpp>
#include <granny.h>
#include <light/light.hpp>








class MeshShader : public Shader
{


#define MAX_BONES 128


	Light *light;



public:


	/**
	Calls basic Shader() and Init()
	*/
	inline MeshShader() : Shader(){ Init(); }
	/**
	Initializes uniforms and light
	*/
	void Init();
	/**
	Cleans data and shader
	*/
	void Clean();


	/**
	Place the model in space
	*/
	void Space(glm::mat4 ModelMatrix, glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix, glm::mat4 NormalMatrix);
	/**
	Place the model in space
	*/
	inline void Space(glm::mat4 ModelMatrix, View * view){ Space(ModelMatrix, view->getViewMatrix(), view->getProjectionMatrix(), glm::transpose(glm::inverse(view->getViewMatrix() * ModelMatrix))); }


	/**
	Send bone information to shader
	*/
	inline void SetGrannyBoneTransform(GLuint numBones, granny_matrix_4x4 GrannyBones[MAX_BONES])
	{ 
		Set("Bones[0]", GrannyBones, numBones); 
	}


	/**
	Send specular values to shader
	*/
	inline void SetSpecular(GLfloat specular_intensity, GLfloat specular_power)
	{
		Set("specular_intensity", specular_intensity);
		Set("specular_power", specular_power);
	}


	/**
	Get light pointer
	*/
	inline Light*getLight(){ return light; }



};









#endif








