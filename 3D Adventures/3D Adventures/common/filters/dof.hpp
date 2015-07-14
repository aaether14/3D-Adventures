#ifndef DOF_HPP
#define DOF_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>





class DofImplementation
{



	TextureObject * dof_texture;
	TextureObject * dof_temp_texture;



public:




	inline DofImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	void Init(GLuint width, GLuint height);




	inline ~DofImplementation(){ this->Clean(); }
	void Clean();



	inline TextureObject * GetDofTexture(){ return this->dof_texture; }
	inline TextureObject * GetDofTempTexture(){ return this->dof_temp_texture; }



};








#endif