

#include "mesh_wrapper.hpp"
#include <shader/shader.hpp>






void MeshWrapper::Init(Controller * ctrl)
{


	this->mesh_shader = new MeshShader();
	this->Drawer = new MeshDrawer(mesh_shader, ctrl);
	this->MeshLight = new Light(mesh_shader);


}




void MeshWrapper::Enable(Controller * ctrl)

{


	this->Drawer->Enable(ctrl);


}



void MeshWrapper::FirstPass(Controller*ctrl)
{



	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();
	Environment * env = settings->GetEnv();
	View * view = ctrl->GetCameraPointer()->GetView();



	this->mesh_shader->Use();



	this->mesh_shader->Set("texture_material", 0);
	this->mesh_shader->Set("shadow_map", 1);
	this->mesh_shader->Set("ssao_map", 2);




	this->mesh_shader->Set("has_ssao", GLfloat(f_settings->SSAO.Enabled));
	this->MeshLight->SetFog(glm::pow(env->fog_color, glm::vec3(2.2)), env->fog_density);




	this->MeshLight->SetLight(env->model_bright*
		glm::pow(env->sun_color, glm::vec3(2.2)),
		glm::vec3(glm::normalize(-view->getViewMatrix() * glm::vec4(env->sun_dir, 0.0))),
		env->model_ambient,
		env->model_diffuse);




	tech->GetShadow()->GetShadowMap()->BindTexture(0, GL_TEXTURE1);
	tech->GetSSAO()->GetSSAOTexture()->BindTexture(0, GL_TEXTURE2);
	tech->GetShadow()->GetShadowMap()->ResetTextureState();



}


void MeshWrapper::Render(Controller*ctrl)
{



	this->Drawer->Draw(ctrl);


}


void MeshWrapper::Clean()
{


	delete this->mesh_shader;


	delete Drawer;
	delete MeshLight;


}






