#ifndef SKYBOX
#define SKYBOX





#include <sky/sky_render.hpp>
#include <shader/shader.hpp>
#include "controls.hpp"






class SkyWrapper : public SkyRender
{




public:


	inline SkyWrapper() : SkyRender(){}
	inline ~SkyWrapper(){ Clean(); }


	void Init();
	void Clean();
	void Enable();



};

#endif