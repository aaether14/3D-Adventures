#ifndef G_BUFFER_HPP
#define G_BUFFER_HPP



#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>




class GBuffer
{


	TextureObject * buffer;
	TextureObject * color_textures[2];


	GLuint texture_index;


public:



	inline GBuffer(GLuint window_width, GLuint window_height){ this->Init(window_width, window_height); }
	void Init(GLuint window_width, GLuint window_height);



	inline ~GBuffer(){ this->Clean(); }
	void Clean();



	inline TextureObject ** GetColorTextures(){ return this->color_textures; }
	inline TextureObject * GetBuffer(){ return this->buffer; }
	inline TextureObject * GetTexture(){ return color_textures[texture_index]; }
	inline TextureObject * GetOtherTexture(){ return color_textures[!texture_index]; }



	inline void Reset(){ texture_index = 0; }
	inline void Switch(){ texture_index = !texture_index; }




};



#endif