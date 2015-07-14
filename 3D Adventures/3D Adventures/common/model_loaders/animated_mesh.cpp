//Checked 2014

#include <GL/glew.h>
#include <glfw3.h>
#include "math_3d.h"
#include "assimp_loader.hpp"
#include "animated_mesh.hpp"



void AnimatedMesh::Init(char*path)
{
	this->mesh = new Mesh();
	mesh->LoadMesh(path);
	long long m_startTime = glfwGetTime();
}



void AnimatedMesh::Animate(float start,float end, float speed)
{
	float RunningTime = (float)((double)glfwGetTime() - (double)this->m_startTime) + start;
	if (RunningTime >= end/speed){
		this->m_startTime = glfwGetTime();
		RunningTime = start;
	}
	this->mesh->BoneTransform(RunningTime *speed, this->transform);

}

