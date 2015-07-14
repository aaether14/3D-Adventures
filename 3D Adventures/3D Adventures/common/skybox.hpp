#ifndef SKYBOX
#define SKYBOX





#include <sky/sky_render.hpp>
#include <shader/shader.hpp>
#include "controls.hpp"






class Skybox
{



	SkyRender * sky_render;
	Shader * sky_shader;



public:



	Skybox();
	~Skybox();
	void Init();
	void Clean();
	void Render(Controller * ctrl, glm::mat4 MVP, glm::mat4 MV);
	void SetUniforms(Controller * ctrl, glm::mat4 MVP, glm::mat4 MV);



};

#endif