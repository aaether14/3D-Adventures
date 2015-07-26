#include "mesh_wrapper.hpp"






void MeshWrapper::Init()
{


	AModule::Add("MeshDrawer", new MeshDrawer());


}




void MeshWrapper::Enable()

{



	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	Get("MeshDrawer")->Enable();


	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));
	FilterSettings * f_settings = static_cast<FilterSettings*>(res->Get("FilterSettings"));
	View * view = ctrl->GetCameraPointer()->GetView();
	Shader::Enable();


	Set("texture_material", 0);
	Set("shadow_map", 1);
	Set("ssao_map", 2);




	Set("has_ssao", GLfloat(f_settings->SSAO.Enabled));
	getLight()->SetFog(glm::pow(env->fog_color, glm::vec3(2.2)), env->fog_density);




	getLight()->SetDirectionalLight(env->model_bright*
		glm::pow(env->sun_color, glm::vec3(2.2)),
		glm::vec3(glm::normalize(-view->getViewMatrix() * glm::vec4(env->sun_dir, 0.0))),
		env->model_ambient,
		env->model_diffuse);




	tech->GetShadow()->GetShadowMap()->BindTexture(0, GL_TEXTURE1);
	tech->GetSSAO()->GetSSAOTexture()->BindTexture(0, GL_TEXTURE2);
	tech->GetShadow()->GetShadowMap()->ResetTextureState();


}




void MeshWrapper::Render()
{


	static_cast<MeshDrawer*>(Get("MeshDrawer"))->Render();


}


void MeshWrapper::Clean()
{


	MeshShader::Clean();
	Get("MeshDrawer")->Clean();


}






