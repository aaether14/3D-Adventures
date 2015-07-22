#ifndef MESH_DRAWER
#define MESH_DRAWER




#include <mesh_shader.hpp>
#include "controls.hpp"
#include <entity/entity_manager.hpp>
#include <converter/assimp_converter.hpp>




#define MAX_BONES 128





class MeshDrawer
{



	MeshShader * shader;
	EntityManager * entity_manager;



public:



	inline   ~MeshDrawer() { this->Clean(); };
	inline   MeshDrawer() {}



	inline MeshDrawer(MeshShader * shader, Controller * ctrl) { this->Init(shader, ctrl); }
	void LoadMeshes(Controller * ctrl);
	void Init(MeshShader * shader, Controller * ctrl);
	void Draw(Controller *ctrl);
	void Clean();
	void Enable(Controller *ctrl);



};

#endif