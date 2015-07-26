#ifndef PIPELINE
#define PIPELINE





#include "controls.hpp"
#include "terrain_wrapper.hpp"
#include "screen_render.hpp"
#include <mesh_implementation/mesh_wrapper.hpp>
#include <sky_implementation/sky_wrapper.hpp>
#include <base/base_module.hpp>






class Pipeline : public AModule
{



	void Init();



	void LightPass();
	void ShadowPass();
	void GeometryPass();



	void ApplyGausBlur(GLuint type,
		TextureObject * tex_source, TextureObject * tex_target,
		GLuint width, GLuint height,
		GLfloat blur_amount);



	void HandleDoF();
	void HandleBloom();
	void HandleSSAO();
	void HandleFXAA();




public:




	inline ~Pipeline(){ this->Clean(); }


	void Enable();
	void Clean();


};

#endif