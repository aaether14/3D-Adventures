/*


Class for managing OpenGL textures and also WTT(write to texture) support
Using FreeImage for loading


*/




#ifndef TEXTURE_HPP
#define TEXTURE_HPP





#include <FreeImage.h>
#include <util/string_helper.hpp>
#include <GL/glew.h>
#include <glfw3.h>
#include <assert.h>
#include <glm/glm.hpp>







#define DebugMsg(str){printf("%s\n",str);}
#define POWER_OF_TWO(x) ( (x > 0) && ((x & (x - 1)) == 0) ) 
#define COLOR_TYPE 0x256
#define DEPTH_TYPE 0x257
#define G_TYPE 0x258







class TextureObject
{



	GLuint m_FBO;


	GLuint *texture;
	GLuint depth;


	GLuint num_tex;
	GLuint width;
	GLuint height;



public:


	inline TextureObject(GLuint num_tex){ this->Init(num_tex); }
	inline void Init(GLuint num_tex){ glGenFramebuffers(1, &this->m_FBO); this->num_tex = num_tex; }

	inline ~TextureObject(){ this->Clean(); }
	inline void Clean(){ glDeleteFramebuffers(1, &m_FBO); glDeleteTextures(num_tex, texture); glDeleteTextures(1, &depth); }


	inline void BindTexture(GLuint id, GLuint tex_unit){ glActiveTexture(tex_unit); glBindTexture(GL_TEXTURE_2D, this->texture[id]); }
	inline void ResetTextureState(){ glActiveTexture(GL_TEXTURE0); }

	inline GLuint *GetTexture(){ return this->texture; }
	inline GLuint GetDepth(){ return this->depth; }


	void WriteTexture(GLuint width, GLuint height);


	void CreateTexture(GLuint tex_type,
		GLenum target,
		GLsizei width, GLsizei height,
		GLint internalFormat, GLint format,
		GLenum type, GLvoid
		* pixels,
		GLint f_param, 
		GLint c_param, 
		glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));



	inline GLuint GetWidth(){ return this->width; }
	inline GLuint GetHeight(){ return this->height; }
	inline void SetViewport(){ glViewport(0, 0, this->width, this->height); }




	static GLuint load_texture(char* file, GLint param_min, GLint param_max);
	static GLuint load_cube_texture(const char *Directory,
		const char *PosXFilename,
		const char *NegXFilename,
		const char *PosYFilename,
		const char *NegYFilename,
		const char *PosZFilename,
		const char *NegZFilename);
	static GLuint create_texture_array(char *Directory, char ** textures, GLuint num, GLfloat aniso);
	static GLuint create_texture_from_color(GLfloat r, GLfloat y, GLfloat z);
	static FIBITMAP *get_dib(char* file);
	static bool readRawFile(char*path, BYTE * bits);
	static int getRawSize(char*path);
	static GLuint create_texture(GLenum target, GLsizei width, GLsizei height, GLint internalFormat, GLint format, GLenum type, GLvoid * pixels,
		GLint f_param, GLint c_param, glm::vec4 b_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	static bool CheckStatus(GLuint fbo);





};






#endif