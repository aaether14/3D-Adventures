/*


Classes for storing any type of view info


*/




#ifndef VIEW_HPP
#define VIEW_HPP




#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stdio.h>





#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif




#define RENDER_DISTANCE 256





class ViewInfo

{

	/*SOME INFO*/

	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 up;
	GLfloat distance;
	GLfloat render_distance;
	GLfloat z_near;
	GLfloat FoV;
	GLfloat ratio;


public:

	inline ViewInfo() { this->Init(); }
	void Init();


	/*SOME MORE INFO*/


	inline void SetFromOther(ViewInfo * other)
	{
		this->position = other->getCameraPos();
		this->direction = other->getDirection();
		this->up = other->getUpVec();
		this->distance = other->getDistance();
		this->render_distance = other->getRenderDistance();
		this->z_near = other->getNear();
		this->FoV = other->getFoV();
		this->ratio = other->getRatio();

	}

	inline glm::vec3 getCameraPos() { return position; }
	inline void setUpVec(glm::vec3 t_vec) { this->up = t_vec; }
	inline glm::vec3 getDirection() { return direction; }
	inline GLfloat getRatio(){ return this->ratio; }
	inline void setRatio(GLfloat ratio) { this->ratio = ratio; }
	inline glm::vec3 getUpVec() { return this->up; }
	inline GLfloat getNear() { return this->z_near; }
	inline void setNear(GLfloat near) { this->z_near = near; }
	inline void SetRenderDistance(GLfloat r_d) { this->render_distance = r_d; }
	inline void SetCameraPos(glm::vec3 pos) { this->position = pos; }
	inline void SetCameraY(GLfloat y) { this->position.y = y; }
	inline void SetDistance(GLfloat new_distance) { this->distance = new_distance; }
	inline void setDirection(glm::vec3 dir) { this->direction = dir; }
	inline GLfloat getFoV() { return this->FoV; }
	inline GLfloat getTanHalfFov(){ return tanf((FoV / 2.0f) * M_PI / 180.0); }
	inline void setFov(GLfloat FoV) { this->FoV = FoV; }
	inline GLfloat getRenderDistance() { return this->render_distance; }
	inline GLfloat getDistance() { return this->distance; };


	/*END OF MORE INFO*/



};


class View
{


	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;


public:


	inline View() {}
	inline void Init(GLint w, GLint h) {}
	void Create3rd(ViewInfo *info);
	void Create1st(ViewInfo *info);
	void Create3rd(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, GLfloat distance, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
	void Create1st(GLfloat FoV, GLfloat ratio, GLfloat z_near, GLfloat z_far, glm::vec3 position, glm::vec3 direction, glm::vec3 up);
	inline glm::mat4 getViewMatrix() { return ViewMatrix; };
	inline glm::mat4 getProjectionMatrix() { return ProjectionMatrix; }
	inline glm::mat4 getCamera(){ return ProjectionMatrix*ViewMatrix; }
	inline void SetProjection(glm::mat4 ProjectionMatrix){ this->ProjectionMatrix = ProjectionMatrix; }
	inline void SetView(glm::mat4 ViewMatrix){ this->ViewMatrix = ViewMatrix; }



};



class Plane

{


public:

	
	glm::vec3 normal;
	GLfloat distance;


	void Normalize();


};



class Frustum
{


	
	Plane*planes;



public:


	inline Frustum() { planes = new Plane[6]; }
	inline ~Frustum() { delete planes; }

    
	inline Plane*getPlanes(){ return planes; }


	void Create(glm::mat4 MVP);





};





#endif