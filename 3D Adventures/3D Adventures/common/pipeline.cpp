#include "pipeline.hpp"







void Pipeline::Init(Controller * ctrl)
{



	this->t_wrapper = new TerrainWrapper(ctrl);
	this->m_wrapper = new MeshWrapper(ctrl);
	this->sky_box = new Skybox();
	this->quad_render = new Aaether2D();



}



void Pipeline::GeometryPass(Controller * ctrl)
{



	Techniques * tech = ctrl->GetGameObject()->GetTechniques();



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tech->GetSSAO()->GetGeometryPassTexture()->WriteTexture(ctrl->GetWindowWidth(), ctrl->GetWindowHeight());
	tech->GetSSAO()->UseGeometryPass();
	tech->GetSSAO()->SetGeometryPass(true);
	tech->GetSSAO()->SetOnMeshRender(0.0);
	this->t_wrapper->Render(ctrl);
	tech->GetSSAO()->SetOnMeshRender(1.0);
	this->m_wrapper->Render(ctrl);
	tech->Unbind();




}



void Pipeline::LightPass(Controller*ctrl)
{




	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();




	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	tech->GetGBuffer()->GetBuffer()->WriteTexture(ctrl->GetWindowWidth(), ctrl->GetWindowHeight());



	glm::mat4 m_rot = Math::Rotate(0, glfwGetTime() / 150.0, 0);


	sky_box->Render(ctrl, view->getCamera()*
		Math::Translation(info->getCameraPos() - info->getDirection()*info->getDistance())*
		m_rot*
		Math::Scale(glm::vec3(info->getRenderDistance())),
		view->getViewMatrix()*
		Math::Translation(info->getCameraPos() - info->getDirection()*info->getDistance())*
		m_rot*
		Math::Scale(glm::vec3(info->getRenderDistance())));





	this->t_wrapper->FirstPass(ctrl);
	this->t_wrapper->Render(ctrl);
	this->m_wrapper->FirstPass(ctrl);
	this->m_wrapper->Render(ctrl);





	tech->ApplyFilter(GAMMA_CORRECTION_FILTER,
		tech->GetGBuffer()->GetBuffer()->GetTexture()[0],
		tech->GetGBuffer()->GetColorTextures()[0],
		ctrl->GetWindowWidth(),
		ctrl->GetWindowHeight());



	tech->Unbind();




}




void Pipeline::ShadowPass(Controller * ctrl)
{


	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	ShadowImplementation * shadow = tech->GetShadow();



	shadow->GetShadowMap()->WriteTexture(ShadowMapWidth, ShadowMapHeight);
	shadow->SetShadowPass(true);
	shadow->Use();



	this->m_wrapper->Render(ctrl);



	this->ApplyGausBlur(0, ctrl, 
		shadow->GetTempShadowMap(), 
		shadow->GetShadowMap(),
		ShadowMapWidth,
		ShadowMapHeight, 
		0.3f);



	tech->Unbind();



}



void Pipeline::HandleDoF(Controller * ctrl)
{


	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();



	if (f_settings->DoF.Enabled)
	{



		Techniques * tech = ctrl->GetGameObject()->GetTechniques();
		DofImplementation * dof = tech->GetDof();



		tech->ApplyFilter(NULL_FILTER,
		tech->GetGBuffer()->GetTexture()->GetTexture()[0],
		dof->GetDofTexture(), 
		dof->GetDofTexture()->GetWidth(),
		dof->GetDofTexture()->GetHeight());



		GLuint blur_passes = 3;
		for (GLuint i = 0; i < blur_passes; i++)
			this->ApplyGausBlur(1, ctrl, 
			dof->GetDofTempTexture(),
			dof->GetDofTexture(),
			dof->GetDofTexture()->GetWidth(),
			dof->GetDofTexture()->GetHeight(),
			2.5 * pow(2, i));




		tech->Unbind();



	}


}



void Pipeline::HandleBloom(Controller * ctrl)
{


	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();



	if (f_settings->HDR.Bloom.Enabled)
	{



		Techniques * tech = ctrl->GetGameObject()->GetTechniques();
		HdrImplementation * hdr = tech->GetHdr();



		tech->RunProgram(BRIGHT_FILTER);
		hdr->SetUniforms(f_settings->HDR.Bloom.Whitepoint);



		tech->ApplyFilter(BRIGHT_FILTER,
			tech->GetGBuffer()->GetColorTextures()[0]->GetTexture()[0], 
			hdr->GetBrightTexture(),
			hdr->GetBrightTexture()->GetWidth(),
			hdr->GetBrightTexture()->GetHeight());



		GLuint blur_passes = 3;
		for (GLuint i = 0; i < blur_passes; i++)
			this->ApplyGausBlur(1, ctrl, 
			hdr->GetBrightTextureTemp(), 
			hdr->GetBrightTexture(),
			hdr->GetBrightTexture()->GetWidth(),
			hdr->GetBrightTexture()->GetHeight(),
			2.5 * pow(2, i));




		tech->GetBasic()->AddTextures(
			tech->GetGBuffer()->GetOtherTexture(),
			tech->GetGBuffer()->GetTexture()->GetTexture()[0],
			hdr->GetBrightTexture()->GetTexture()[0],
			ctrl->GetWindowSize());


		tech->GetGBuffer()->Switch();
		tech->Unbind();


	}



}




void Pipeline::HandleFXAA(Controller * ctrl)
{


	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();



	if (f_settings->FXAA.Enabled)
	{


		Techniques * tech = ctrl->GetGameObject()->GetTechniques();
		FXAAImplementation * fxaa = tech->GetFXAA();




		tech->RunProgram(FXAA_FILTER);
		tech->GetFXAA()->SetUniforms(f_settings->FXAA.span_max, f_settings->FXAA.reduce_min, f_settings->FXAA.reduce_mul);



		tech->ApplyFilter(FXAA_FILTER,
			tech->GetGBuffer()->GetTexture()->GetTexture()[0],
			tech->GetGBuffer()->GetOtherTexture(),
			ctrl->GetWindowWidth(),
			ctrl->GetWindowHeight());



		tech->GetGBuffer()->Switch();
		tech->Unbind();





	}




}





void Pipeline::HandleSSAO(Controller * ctrl)
{


	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();



	if (f_settings->SSAO.Enabled)
	{



		View * view = ctrl->GetCameraPointer()->GetView();
		ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
		Techniques * tech = ctrl->GetGameObject()->GetTechniques();
		SSAOImplementation * ssao = tech->GetSSAO();



		tech->RunProgram(SSAO_FILTER);


		ssao->SetUniforms(view->getProjectionMatrix(), f_settings->SSAO.Radius,
			info->getRatio(), info->getTanHalfFov(), f_settings->SSAO.Power, f_settings->SSAO.NumSamples);


		tech->ApplyFilter(SSAO_FILTER, ssao->GetGeometryPassTexture()->GetDepth(), 
			ssao->GetSSAOTempTexture(),
			ctrl->GetWindowWidth(),
		    ctrl->GetWindowHeight());



		tech->ApplyFilter(SSAO_BLUR, 
			ssao->GetSSAOTempTexture()->GetTexture()[0],
			ssao->GetSSAOTexture(),
			ctrl->GetWindowWidth(),
			ctrl->GetWindowHeight());



		tech->Unbind();




	}

}


void Pipeline::Render(Controller*ctrl)
{


	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	Settings * settings = ctrl->GetGameObject()->GetSettings();
	FilterSettings * f_settings = settings->GetFilterSettings();



	t_wrapper->Enable(ctrl);
	m_wrapper->Enable(ctrl);


	this->GeometryPass(ctrl);
	this->HandleSSAO(ctrl);


	this->ShadowPass(ctrl);
	this->LightPass(ctrl);


	tech->GetGBuffer()->Reset();


	this->HandleDoF(ctrl);
	this->HandleBloom(ctrl);
	this->HandleFXAA(ctrl);



	this->quad_render->Render(
		tech->GetGBuffer()->GetTexture()->GetTexture()[0],
		tech->GetGBuffer()->GetBuffer()->GetDepth(),
		tech->GetDof()->GetDofTexture()->GetTexture()[0],
	    GLfloat(f_settings->DoF.Enabled),
		f_settings->HDR.Bloom.Whitepoint,
		ctrl->GetWindowSize());

}




void Pipeline::Clean()
{

	this->m_wrapper->Clean();
	this->t_wrapper->Clean();
	delete sky_box;
	delete quad_render;

}




void Pipeline::ApplyGausBlur(GLuint type,
	Controller * ctrl,
	TextureObject * tex_source, TextureObject * tex_target,
	GLuint width, GLuint height,
	GLfloat blur_amount)
{



	Techniques * tech = ctrl->GetGameObject()->GetTechniques();



	if (type == 0)
	{
		tech->RunProgram(GAUS_BLUR_SHADER);
		tech->GetBlur()->SetBlurScale1(glm::vec3(0.0f, 1.0f / width * blur_amount, 0.0f));
		tech->ApplyFilter(GAUS_BLUR_SHADER, tex_target->GetTexture()[0], tex_source, width, height);
		tech->GetBlur()->SetBlurScale1(glm::vec3(1.0f / width * blur_amount, 0.0f, 0.0f));
		tech->ApplyFilter(GAUS_BLUR_SHADER, tex_source->GetTexture()[0], tex_target, width, height);
	}
	else if (type == 1)
	{
		tech->RunProgram(GAUS_BLUR_SHADER2);
		tech->GetBlur()->SetBlurScale2(glm::vec3(0.0f, 1.0f / width * blur_amount, 0.0f));
		tech->ApplyFilter(GAUS_BLUR_SHADER2, tex_target->GetTexture()[0], tex_source, width, height);
		tech->GetBlur()->SetBlurScale2(glm::vec3(1.0f / width * blur_amount, 0.0f, 0.0f));
		tech->ApplyFilter(GAUS_BLUR_SHADER2, tex_source->GetTexture()[0], tex_target, width, height);
	}

}






///----------------


