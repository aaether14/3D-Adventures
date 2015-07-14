#ifndef CAMERA_HPP
#define CAMERA_HPP




#include <controller/controls_source.hpp>
#include <util/view.hpp>




class Camera
{


	GLfloat speed, mouse_speed, rotation_speed, base_speed;
	GLdouble horizontalAngle;
	GLdouble verticalAngle;
	GLdouble last_x, last_y;



	View *view_3rd;
	ViewInfo *info;
	Frustum * frustum;


public:


	inline Camera(){ this->Init(); }
	void Init();


	inline ~Camera(){ this->Clean(); }
	void Clean();



	inline View * GetView() { return this->view_3rd; };
	inline ViewInfo *GetInfo() { return this->info; }
	inline Frustum *GetFrustum() { return this->frustum; }



	inline GLfloat GetBaseSpeed(){ return this->base_speed; }
	inline void SetBaseSpeed(GLfloat base_speed){ this->base_speed = base_speed; }


	inline void SetFrustum(glm::mat4 MVP) { this->frustum->Create(MVP); }


	void ComputeAngles(ControllerSource * source);
	void SetInfo(ControllerSource * source);
	void ProcessInput(ControllerSource * source);


	inline void setHorizontalAngle(GLfloat angle){ this->horizontalAngle = angle; }
	inline void setVerticalAngle(GLfloat angle){ this->verticalAngle = angle; }
	inline GLdouble getHorizontalAngle() { return this->horizontalAngle; };
	inline GLdouble getVerticalAngle() { return this->verticalAngle; }




};


#endif