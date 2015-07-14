#ifndef SIMPLE_2D_HPP
#define SIMPLE_2D_HPP


#include <GL/glew.h>
#include <util/controller_math.hpp>
#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/utils.hpp>



class Aaether2D
{



	Shader * shader2d;
	Quad * quad;




public:


	inline Aaether2D(){this->Init(); }
	void Init();

	inline ~Aaether2D(){ this->Clean(); }
	void Clean();


	void Render(GLuint texture,
		GLuint texture1,
		GLuint texture2,
		GLfloat use_dof,
		GLfloat white_point,
		glm::ivec2 window_size);




};



#endif