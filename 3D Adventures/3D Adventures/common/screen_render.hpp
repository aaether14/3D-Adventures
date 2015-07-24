#ifndef SIMPLE_2D_HPP
#define SIMPLE_2D_HPP




#include <GL/glew.h>
#include <util/math_helper.hpp>
#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/utils.hpp>




/*


Class for combining all textures from deffered process


*/
class ScreenRender
{



	Shader * shader2d;
	Quad * quad;




public:


	/**
	Calls Init()
	*/
	inline ScreenRender(){this->Init(); }
	/**
	Initializes shader and quad
	*/
	void Init();


	/**
	Calls Clean()
	*/
	inline ~ScreenRender(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Combines textures and renders to screen
	*/
	void Render(GLuint texture,
		GLuint texture1,
		GLuint texture2,
		GLfloat use_dof,
		GLfloat white_point,
		glm::ivec2 window_size);




};



#endif