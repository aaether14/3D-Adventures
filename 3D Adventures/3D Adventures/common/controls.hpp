#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <camera_implementation/camera.hpp>
#include <util/file_helper.hpp>
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
	Clean engine's data
	*/
	void Clean();
	/**
	Calls Clean()
	*/
	inline  ~Controller(){ this->Clean(); }
	


	/**
	Calls ControllerSource constructor
	*/
	inline Controller() : ControllerSource() {}


	/**
	Initializes Controller Source, camera and game object
	*/
	void Init();


};




#endif