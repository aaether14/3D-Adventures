#include "technique.hpp"










bool Techniques::Create(GLuint window_width, GLuint window_height, 
	GLuint shadow_width, GLuint shadow_height,
	GLuint dof_width, GLuint dof_height,
	GLuint bright_width, GLuint bright_height)
{




	this->basic_filter_implementation = new BasicFilterImplementation();
	this->ssao_implementation = new SSAOImplementation(window_width, window_height);
	this->shadow_implementation = new ShadowImplementation(shadow_width, shadow_height);
	this->blur_implementation = new BlurImplementation();
	this->dof_implementation = new DofImplementation(dof_width, dof_height);
	this->hdr_implementation = new HdrImplementation(bright_width, bright_height);
	this->fxaa_implementation = new FXAAImplementation();
	this->g_buffer = new GBuffer(window_width, window_height);





	return true;
	
}







void Techniques::Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height)
{


	tex_target->WriteTexture(width, height);
	this->RunProgram(prog_target);


}



void Techniques::Unbind()
{


	this->shadow_implementation->SetShadowPass(false);
	this->ssao_implementation->SetGeometryPass(false);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glUseProgram(0);


	this->g_buffer->GetBuffer()->SetViewport();


}





void Techniques::ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height)
{



	this->Bind(prog_target, tex_target, width, height);




	if (prog_target == NULL_FILTER)
		this->basic_filter_implementation->BindNullTexture();
	else if (prog_target == GAUS_BLUR_SHADER)
		this->blur_implementation->BindGausBlurTexture1();
	else if (prog_target == GAUS_BLUR_SHADER2)
		this->blur_implementation->BindGausBlurTexture2();
	else if (prog_target == BRIGHT_FILTER)
		this->hdr_implementation->BindBrightTexture();
	else if (prog_target == SSAO_FILTER)
		this->ssao_implementation->BindSSAOTexture();
	else if (prog_target == SSAO_BLUR)
		this->ssao_implementation->BindBlurTexture();
	else if (prog_target == GAMMA_CORRECTION_FILTER)
		this->basic_filter_implementation->BindGammaTexture();
	else if (prog_target = FXAA_FILTER)
		this->fxaa_implementation->BindFxaaTexture();



		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_source);
		GetBasic()->GetQuad()->Render();




}





void Techniques::RunProgram(GLuint prog_target)
{

	if (prog_target == DEPTH_SHADER)
		this->shadow_implementation->Use();
	else if (prog_target == NULL_FILTER)
		this->basic_filter_implementation->GetNullFilter()->Use();
	else if (prog_target == GAUS_BLUR_SHADER)
		this->blur_implementation->GetGausBlur1()->Use();
	else if (prog_target == GAUS_BLUR_SHADER2)
		this->blur_implementation->GetGausBlur2()->Use();
	else if (prog_target == BRIGHT_FILTER)
		this->hdr_implementation->GetBrightShader()->Use();
	else if (prog_target == SSAO_FILTER)
		this->ssao_implementation->Use();
	else if (prog_target == SSAO_BLUR)
		this->ssao_implementation->UseBlur();
	else if (prog_target == GAMMA_CORRECTION_FILTER)
		this->basic_filter_implementation->GetGammaFilter()->Use();
	else if (prog_target == GEOMETRY_PASS)
		this->ssao_implementation->UseGeometryPass();
	else if (prog_target == FXAA_FILTER)
		this->fxaa_implementation->GetFxaaFilter()->Use();


}





void Techniques::Clean()
{



	delete basic_filter_implementation;
	delete ssao_implementation;
	delete shadow_implementation;
	delete blur_implementation;
	delete dof_implementation;
	delete hdr_implementation;
	delete fxaa_implementation;
	delete g_buffer;




}