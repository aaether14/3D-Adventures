#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <camera_implementation/camera.hpp>
#include "game_object.hpp"







/**
Derives from controller source in order to hold engine data like camera, filters and scene resources
*/
class Controller : public ControllerSource
{


	Camera * camera;
	GameObject * g_obj;



public:



	/**
	Get pointer to camera object
	*/
	inline Camera * GetCameraPointer(){ return this->camera; }
	/**
	Get pointer to game object
	*/
	inline GameObject * GetGameObject(){ return this->g_obj; }



	/**
	Enable controller source and camera computations
	*/
	void Enable();
	/**
	Load a certain project
	*/
	void Load(char*path);


	/**
	Clean engine's data
	*/
	void Clean();
	/**
	Calls Clean()
	*/
	inline  ~Controller(){ this->Clean(); }
	


	/**
	Calls Init()
	*/
	inline Controller(GLint width, GLint height, GLboolean fullscreen, GLchar * title, GLuint major, GLuint minor) : 
		ControllerSource() 
	{ this->Init(width, height, fullscreen, title, major, minor); }


	/**
	Initializes Controller Source, camera and game object
	*/
	void Init(GLint width, GLint height, GLboolean fullscreen, GLchar * title, GLuint major, GLuint minor);


};




#endif