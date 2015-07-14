#ifndef SSAO_HPP
#define SSAO_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/controller_math.hpp>




#define MAX_BONES 128





class SSAOImplementation
{

	//SSAO PASS

	const static GLuint KERNEL_SIZE = 128;


	Shader * ssao_shader;
	TextureObject * ssao_texture;
	TextureObject * ssao_temp_texture;
	TextureObject * geometry_pass_texture;


	GLuint noise_texture;
	GLuint window_width, window_height;
	void Init(GLuint width, GLuint height);
	void Clean();


	//SSAO BLUR

	Shader * ssao_blur;


	//SSAO Geometry Pass

	Shader * geometry_pass;
	GLboolean on_geometry_pass;


public:


	inline SSAOImplementation(GLuint width, GLuint height){ this->Init(width, height); }
	inline ~SSAOImplementation(){ this->Clean(); }


	inline TextureObject * GetSSAOTexture(){ return this->ssao_texture; }
	inline TextureObject * GetSSAOTempTexture(){ return this->ssao_temp_texture; }
	inline TextureObject * GetGeometryPassTexture(){ return this->geometry_pass_texture; }
	inline GLuint GetNoiseTexture(){ return this->noise_texture; }


	inline void Use(){ this->ssao_shader->Use(); }
	inline void UseBlur(){ this->ssao_blur->Use(); }
	inline void UseGeometryPass(){ this->geometry_pass->Use(); }


	inline void BindBlurTexture(){ this->ssao_blur->Set("texture", 0); }


	void GenKernel();
	void GenerateNoiseTexture(GLuint size);


	void SetUniforms(glm::mat4 proj, GLfloat radius, GLfloat aspect, GLfloat tan_fov, GLfloat power, GLint num_samples);
	void SetGeometryPassUniforms(glm::mat4 MVP, glm::mat4 MV);
	inline void SetGrannyBoneTransform(GLuint numBones, granny_matrix_4x4 GrannyBones[MAX_BONES]){ this->geometry_pass->Set("Bones[0]", GrannyBones, numBones); }
	inline void SetOnMeshRender(GLfloat on_mesh_render){ this->geometry_pass->Set("on_mesh_render", on_mesh_render); }


	inline GLboolean OnGeometryPass(){ return this->on_geometry_pass; }
	inline void SetGeometryPass(GLboolean on_geometry_pass){ this->on_geometry_pass = on_geometry_pass; }


	inline void SetTex1(){ this->ssao_shader->Set("gDepthMap", 0); }
	inline void SetTex2(){ this->ssao_shader->Set("gNormalMap", 1); }
	inline void SetTex3(){ this->ssao_shader->Set("gNoiseMap", 2); }


	void BindSSAOTexture();


	inline GLuint GetWidth(){ return this->window_width; }
	inline GLuint GetHeight(){ return this->window_height; }


};




#endif