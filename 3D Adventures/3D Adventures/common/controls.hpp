#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <camera_implementation/camera.hpp>
#include "game_object.hpp"





class Controller : public ControllerSource
{


	Camera * camera;
	GameObject * g_obj;



public:



	inline Camera * GetCameraPointer(){ return this->camera; }
	inline GameObject * GetGameObject(){ return this->g_obj; }



	void Enable();
	void Load(char*path);


	void Clean();
	inline  ~Controller(){ this->Clean(); }
	


	inline Controller(GLint width, GLint height, GLboolean fullscreen, GLchar * title, GLuint major, GLuint minor) : 
		ControllerSource() 
	{ this->Init(width, height, fullscreen, title, major, minor); }

	void Init(GLint width, GLint height, GLboolean fullscreen, GLchar * title, GLuint major, GLuint minor);


};




#endif