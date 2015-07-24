#ifndef PIPELINE
#define PIPELINE





#include "controls.hpp"
#include "mesh_wrapper.hpp"
#include "terrain_wrapper.hpp"
#include "skybox.hpp"
#include "screen_render.hpp"





class Pipeline
{



	MeshWrapper *m_wrapper;
	TerrainWrapper *t_wrapper;
	Skybox * sky_box;
	ScreenRender * screen_render;




public:



	inline Pipeline(Controller * ctrl){ this->Init(ctrl); }
	inline ~Pipeline(){ this->Clean(); }
	void Init(Controller * ctrl);



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


	void Render(Controller *ctrl);
	void Clean();


};

#endif