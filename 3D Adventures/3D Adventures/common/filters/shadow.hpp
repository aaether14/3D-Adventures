/*



Exponential shadow mapping 



*/



#ifndef SHADOW_HPP
#define SHADOW_HPP



#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/math_helper.hpp>
#include <settings/environment.hpp>




#define ShadowMapWidth 1024
#define ShadowMapHeight 1024





class ShadowImplementation
{


	Shader * shadow_shader;
	TextureObject * shadow_map;
	TextureObject * temp_shadow_map;


	GLuint width, height;
	GLboolean on_shadow_pass;
	GLfloat shadow_size;


public:


	inline ShadowImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	void Init(GLuint width, GLuint height);


	inline ~ShadowImplementation(){ this->Clean(); }
	void Clean();


	inline void Use(){ this->shadow_shader->Use(); }
	inline TextureObject * GetShadowMap(){ return this->shadow_map; }
	inline TextureObject * GetTempShadowMap(){ return this->temp_shadow_map; }


	inline GLboolean OnShadowPass(){ return this->on_shadow_pass; }
	inline void SetShadowPass(GLboolean on_shadow_pass){ this->on_shadow_pass = on_shadow_pass; }


	inline void UniformMVP(glm::mat4 MVP){ this->shadow_shader->Set("depthMVP", MVP); }
	inline void SetGrannyBoneTransform(GLuint numBones, granny_matrix_4x4 *GrannyBones){ this->shadow_shader->Set("Bones[0]", GrannyBones, numBones); }


	glm::mat4 GetDirectionalShadow(Environment * env, ViewInfo * info);



};


#endif