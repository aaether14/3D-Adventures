#ifndef MESH_DRAWER
#define MESH_DRAWER




#include "uniform.hpp"
#include <util/controller_math.hpp>
#include "controls.hpp"
#include <granny.h>
#include <model_loaders/animated_mesh.hpp>
#include <model_loaders/granny_loader.h>
#include <model_loaders/aaether_loader.hpp>
#include <entity/static.hpp>





#define MAX_BONES 128





class MeshDrawer
{


	MeshShader * shader;
	StaticManager * s_manager;


public:


	inline   ~MeshDrawer() { this->Clean(); };
	inline   MeshDrawer() {}


	inline MeshDrawer(MeshShader * shader, Controller * ctrl) { this->Init(shader, ctrl); }
	void LoadMeshes(Controller * ctrl);
	void Init(MeshShader * shader, Controller * ctrl);
	void Draw(Controller *ctrl);
	//void TransformMesh(AnimatedMesh *mesh);
	void Clean();
	void Enable(Controller *ctrl);



};

#endif