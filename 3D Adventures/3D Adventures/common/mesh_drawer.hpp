#ifndef MESH_DRAWER
#define MESH_DRAWER




#include "uniform.hpp"
#include <util/controller_math.hpp>
#include "controls.hpp"
#include <granny.h>
#include <model_loaders/animated_mesh.hpp>
#include <model_loaders/granny_loader.h>
#include <model_loaders/aaether_loader.hpp>
#include <entity/creature.hpp>
#include <entity/static.hpp>





#define MAX_BONES 128





class MeshDrawer
{
	/*Things not to mess up with*/


	MeshShader * shader;


	/*
	inline void SetBoneTransform(GLuint index, Matrix4f tr){glUniformMatrix4fv(this->u_data->BoneLocation, 1, GL_TRUE, (const GLfloat *)tr.m);}
	inline void SetGrannyBoneIndex(granny_matrix_4x4 gr, GLuint what_pos){glUniformMatrix4fv(this->u_data->BoneLocation + what_pos, 1, GL_FALSE, (GLfloat *)gr);}
	*/


	/*Things to mess up with*/


	CreatureManager *c_manager;
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