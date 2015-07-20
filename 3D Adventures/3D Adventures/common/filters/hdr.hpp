/*


High Dynamic Range including Bloom, Tone mapping, white points and basic exposure
WIP


*/




#ifndef HDR_HPP
#define HDR_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/math_helper.hpp>





class HdrImplementation
{



	Shader * bright_shader;
	TextureObject * bright_texture;
	TextureObject * bright_texture_temp;




public:





	inline HdrImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	void Init(GLuint width, GLuint height);




	inline ~HdrImplementation(){ this->Clean(); }
	void Clean();




	inline TextureObject * GetBrightTexture(){ return this->bright_texture; }
	inline TextureObject * GetBrightTextureTemp(){ return this->bright_texture_temp; }



	inline Shader * GetBrightShader(){ return this->bright_shader; }
	inline void BindBrightTexture(){ this->bright_shader->Set("texture", 0); }


	void SetUniforms(GLfloat white_point);




};





#endif