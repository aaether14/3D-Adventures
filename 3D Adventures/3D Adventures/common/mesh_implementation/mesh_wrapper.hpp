#ifndef MESH_WRAPPER
#define MESH_WRAPPER




#include "mesh_drawer.hpp"





/**
Wraps mesh functionality
*/
class MeshWrapper : public MeshShader
{

	



public:



	/**
	Initializes data
	*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Enables wrapper functionality
	*/
	void Enable();

	/**
	Renders geometry
	*/
	void Render();




};


#endif