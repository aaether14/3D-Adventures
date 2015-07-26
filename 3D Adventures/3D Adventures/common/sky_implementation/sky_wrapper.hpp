#ifndef SKYBOX
#define SKYBOX





#include "sky_render.hpp"
#include <shader/shader.hpp>
#include "controls.hpp"





/**
Wrapping skydome functionality connecting it to the engine
*/
class SkyWrapper : public SkyRender
{




public:


	/**
	Initializes previous components
	*/
	inline SkyWrapper() : SkyRender(){}
	/**
	Calls Clean()
	*/
	inline ~SkyWrapper(){ Clean(); }


	/**
	Initializes data
	*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Affects the scene by rendering
	*/
	void Enable();



};

#endif