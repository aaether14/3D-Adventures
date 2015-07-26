#ifndef MESH_DRAWER
#define MESH_DRAWER




#include "mesh_shader.hpp"
#include "controls.hpp"
#include <entity/entity_manager.hpp>
#include <base/base_module.hpp>




#define MAX_BONES 128





/**
Holds entity manager
*/
class MeshDrawer : public AModule
{



	EntityManager * entity_manager;



public:



	/**
	Initialize entity manager
	*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Enables entity manager
	*/
	void Enable();
	/**
	Renders entities
	*/
	void Render();



};

#endif