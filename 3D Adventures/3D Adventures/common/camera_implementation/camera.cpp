#include "camera.hpp"




void Camera::Init()
{



	this->verticalAngle = -M_PI / 24;
	this->horizontalAngle = 3.14f;
	this->base_speed = this->speed = 20.0f;
	this->mouse_speed = 0.0025f;
	this->rotation_speed = M_PI;



	this->view_3rd = new View();
	this->info = new ViewInfo();
	this->frustum = new Frustum();



}



void Camera::Clean()
{

	delete view_3rd;
	delete info;
	delete frustum;


}



void Camera::ProcessInput(ControllerSource * source)
{


	if (source->GetKey(GLFW_KEY_LEFT_SHIFT))
		this->speed = 3 * this->base_speed;
	else
		this->speed = this->base_speed;



	if (source->GetKey(GLFW_KEY_W))
		this->info->SetCameraPos(this->info->getCameraPos() +
		glm::normalize(glm::vec3(this->info->getDirection().x, 0.0, this->info->getDirection().z))
		* GLfloat(source->GetFpsPointer()->Delta()) * speed);





	if (source->GetKey(GLFW_KEY_A))
		horizontalAngle += source->GetFpsPointer()->Delta()*this->rotation_speed;



	if (source->GetKey(GLFW_KEY_D))
		horizontalAngle -= source->GetFpsPointer()->Delta()*this->rotation_speed;



}





void Camera::ComputeAngles(ControllerSource * source){



	GLdouble delta_x, delta_y;



	if (glfwGetMouseButton(source->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT))
	{


		glfwGetCursorPos(source->GetWindow(), &delta_x, &delta_y);
		glfwSetCursorPos(source->GetWindow(), this->last_x, this->last_y);



		delta_x = this->mouse_speed * GLdouble(this->last_x - delta_x);
		delta_y = this->mouse_speed * GLdouble(this->last_y - delta_y);


		this->horizontalAngle += delta_x;
		this->verticalAngle += delta_y;

		if (verticalAngle > -M_PI / 24)
			verticalAngle = -M_PI / 24;
		if (verticalAngle < -M_PI / 2)
			verticalAngle = -M_PI / 2;


	}
	else
	{
		glfwGetCursorPos(source->GetWindow(), &this->last_x, &this->last_y);
	}


	this->SetInfo(source);


	glfwSetInputMode(source->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);



}





void Camera::SetInfo(ControllerSource * source)
{

	this->info->setDirection(glm::vec3(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
		));

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
		);


	info->setUpVec(glm::cross(right, info->getDirection()));


	info->setRatio(GLfloat(source->GetWindowWidth()) / GLfloat(source->GetWindowHeight()));
	info->setNear(1.0f);


	glm::vec3 old = info->getCameraPos();
	info->SetCameraPos
		(
		old +
		2.0f*glm::normalize(glm::vec3(info->getDirection().x, 0, info->getDirection().z)
		+ glm::vec3(0, 1, 0)
		));


	this->view_3rd->Create3rd(info);
	this->info->SetCameraPos(old);



}