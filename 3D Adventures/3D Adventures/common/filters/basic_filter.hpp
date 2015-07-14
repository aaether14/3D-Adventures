#ifndef BASIC_FILTER_HPP
#define BASIC_FILTER_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>
#include <util/utils.hpp>





class BasicFilterImplementation
{


	Shader * null_filter;
	Shader * gamma_filter;


	Shader * add_shader;
	Shader * mult_shader;


	Quad * m_quad;



public:



	inline BasicFilterImplementation(){ this->Init(); }
	void Init();


	inline ~BasicFilterImplementation(){ this->Clean(); }
	void Clean();



	inline Shader * GetNullFilter(){ return this->null_filter; }
	inline Shader * GetGammaFilter(){ return this->gamma_filter; }



	inline void BindNullTexture(){ this->null_filter->Set("texture", 0); }
	inline void BindGammaTexture(){ this->gamma_filter->Set("texture", 0); }



	void MultTextures(TextureObject * target, GLuint tex1, GLuint tex2, glm::ivec2 window_size);
	void AddTextures(TextureObject * target, GLuint tex1, GLuint tex2, glm::ivec2 window_size);


	inline Quad * GetQuad(){ return m_quad; }


};





#endif