#ifndef CONTROLS_HPP
#define CONTROLS_HPP





#include <camera_implementation/camera.hpp>
#include <util/file_helper.hpp>







/**
Derives from controller source in order to hold engine data like camera, filters and scene resources
*/
class Controller : public ControllerSource
{




public:




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