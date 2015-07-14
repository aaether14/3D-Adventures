#ifndef UTILS_HPP
#define UTILS_HPP



#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>



class Quad
{


	GLuint m_VAO, m_VBO;



public:



	inline Quad(){ this->Init(); }
	void Init();


	inline ~Quad(){ this->Clean(); }
	void Clean();



	void Render();


};



#endif