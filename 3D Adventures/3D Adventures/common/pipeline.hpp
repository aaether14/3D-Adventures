#ifndef PIPELINE
#define PIPELINE





#include "controls.hpp"
#include "mesh_wrapper.hpp"
#include "terrain_wrapper.hpp"
#include "sky_wrapper.hpp"
#include "screen_render.hpp"
#include <base/base_module.hpp>






class Pipeline : public AModule
{



	ScreenRender * screen_render;




public:




	inline ~Pipeline(){ this->Clean(); }
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


	void Enable();
	void Clean();


};

#endif