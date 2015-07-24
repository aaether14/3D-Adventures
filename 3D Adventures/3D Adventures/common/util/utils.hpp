#ifndef UTILS_HPP
#define UTILS_HPP



#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/math_helper.hpp>





/**


Just a class to provide quads for WTT


*/
class Quad
{


	GLuint m_VAO, m_VBO;



public:



	/**
	Calls Init()
	*/
	inline Quad(){ this->Init(); }
	/**
	Initializes data
	*/
	void Init();


	/**
	Calls Clean()
	*/
	inline ~Quad(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Renders quad
	*/
	void Render();


};



#endif