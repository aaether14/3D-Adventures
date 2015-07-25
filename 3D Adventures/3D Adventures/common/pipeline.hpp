#ifndef PIPELINE
#define PIPELINE





#include "controls.hpp"
#include "mesh_wrapper.hpp"
#include "terrain_wrapper.hpp"
#include "skybox.hpp"
#include "screen_render.hpp"
#include <base/base_module.hpp>




class Pipeline : public AModule
{



	MeshWrapper *m_wrapper;
	TerrainWrapper *t_wrapper;
	Skybox * sky_box;
	ScreenRender * screen_render;




public:




	inline ~Pipeline(){ this->Clean(); }
	void Init();



	void LightPass(Controller*ctrl);
	void ShadowPass(Controller * ctrl);
	void GeometryPass(Controller * ctrl);



	void ApplyGausBlur(GLuint type,
		Controller * ctrl, 
		TextureObject * tex_source, TextureObject * tex_target,
		GLuint width, GLuint height,
		GLfloat blur_amount);



	void HandleDoF(Controller * ctrl);
	void HandleBloom(Controller * ctrl);
	void HandleSSAO(Controller * ctrl);
	void HandleFXAA(Controller * ctrl);


	void Enable();
	void Clean();


};

#endif