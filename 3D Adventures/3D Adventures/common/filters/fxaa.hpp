#ifndef FXAA_HPP
#define FXAA_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>





class FXAAImplementation
{


	Shader * fxaa_shader;



public:




	inline FXAAImplementation(){ this->Init(); }
	void Init();




	inline ~FXAAImplementation(){ this->Clean(); }
	void Clean();



	inline Shader * GetFxaaFilter(){ return this->fxaa_shader; }
	inline void BindFxaaTexture(){ this->fxaa_shader->Set("R_filterTexture", 0); }


	void SetUniforms(GLfloat span_max, GLfloat reduce_min, GLfloat reduce_mul);



};




#endif 