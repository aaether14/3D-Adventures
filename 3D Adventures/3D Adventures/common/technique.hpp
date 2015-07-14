#ifndef TECHNIQUE_HPP
#define TECHNIQUE_HPP




#include <filters/ssao.hpp>
#include <filters/shadow.hpp>
#include <filters/g_buffer.hpp>
#include <filters/blur.hpp>
#include <filters/dof.hpp>
#include <filters/hdr.hpp>
#include <filters/basic_filter.hpp>
#include <filters/fxaa.hpp>








#define NULL_FILTER 11
#define DEPTH_SHADER 12
#define GAUS_BLUR_SHADER 13
#define GAUS_BLUR_SHADER2 14
#define BRIGHT_FILTER 15
#define SSAO_FILTER 16
#define SSAO_BLUR 17
#define GAMMA_CORRECTION_FILTER 18
#define GEOMETRY_PASS 19
#define FXAA_FILTER 20





class Techniques
{




	BasicFilterImplementation * basic_filter_implementation;
	SSAOImplementation * ssao_implementation;
	ShadowImplementation * shadow_implementation;
	BlurImplementation * blur_implementation;
	DofImplementation * dof_implementation;
	HdrImplementation * hdr_implementation;
	FXAAImplementation * fxaa_implementation;
	GBuffer * g_buffer;




public:






	bool Create(GLuint window_width, GLuint window_height, 
		GLuint shadow_width, GLuint shadow_height,
		GLuint dof_width, GLuint dof_height,
		GLuint bright_width, GLuint bright_height);



	inline ~Techniques(){ this->Clean(); }
	void Clean();




	void Bind(GLuint prog_target, TextureObject * tex_target, GLuint width, GLuint height);
	void ApplyFilter(GLuint prog_target, GLuint tex_source, TextureObject * tex_target, GLuint width, GLuint height);
	void Unbind();
	void RunProgram(GLuint prog_target);





	inline BasicFilterImplementation * GetBasic(){ return this->basic_filter_implementation; }
	inline SSAOImplementation * GetSSAO(){ return this->ssao_implementation; }
	inline ShadowImplementation * GetShadow(){ return this->shadow_implementation; }
	inline BlurImplementation * GetBlur(){ return this->blur_implementation; }
	inline DofImplementation * GetDof(){ return this->dof_implementation; }
	inline HdrImplementation * GetHdr(){ return this->hdr_implementation; }
	inline FXAAImplementation * GetFXAA(){ return this->fxaa_implementation; }
	inline GBuffer * GetGBuffer(){ return g_buffer; }








	

};




#endif