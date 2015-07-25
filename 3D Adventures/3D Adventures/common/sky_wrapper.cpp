#include "sky_wrapper.hpp"






void SkyWrapper::Init()
{





	LoadCube("data/objects/sphere/dusk/",
		"px.jpg",
		"nx.jpg",
		"py.jpg",
		"ny.jpg",
		"pz.jpg",
		"nz.jpg");



}

void SkyWrapper::Clean()
{

	SkyRender::Clean();


}







void SkyWrapper::Enable()
{
	


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
	View * view = ctrl->GetCameraPointer()->GetView();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));





	glm::mat4 m_rot = Math::Rotate(0, glfwGetTime() / 150.0, 0);
	glm::mat4 ModelMatrix = Math::Translation(info->getCameraPos() - info->getDirection()*info->getDistance())*
		m_rot*
		Math::Scale(glm::vec3(info->getRenderDistance()));





	Shader::Enable();
	Set("cube", 0);
    Set("MVP", view->getCamera()*ModelMatrix);
	Set("MV", view->getViewMatrix() * ModelMatrix);
	glm::vec4 f = glm::vec4(env->fog_color, 1.0);
	Set("fog_color", f);



	SkyRender::Enable();
	Stop();



}