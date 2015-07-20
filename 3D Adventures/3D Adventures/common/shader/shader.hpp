/*


Shader class for which makes for easy uniform management using std::map


*/





#ifndef SHADER_HPP
#define SHADER_HPP



#include <util/string_helper.hpp>
#include <map>
#include <GL/glew.h>
#include <util/math_helper.hpp>




class Shader
{


	GLuint program;
	std::map<std::string, GLuint> uniforms;


public:


	inline Shader(){ this->Init(); }
	inline ~Shader(){ this->Clean(); }
	inline void Init(){this->program = glCreateProgram(); }
	inline void Clean(){ glDeleteProgram(this->program); this->uniforms.clear(); }


	void Add(char * path, GLenum type);
	void Link();
	inline void Use(){ glUseProgram(program); }
	inline void Stop(){ glUseProgram(0); }


	inline void AddVariable(char * name)	{ this->uniforms[name] = glGetUniformLocation(this->program, name); }
	inline void Set(char * name, GLint v){ glUniform1i(this->uniforms[name], v); }
	inline void Set(char * name, GLfloat v){ glUniform1f(this->uniforms[name], v); }
	inline void Set(char * name, GLdouble v){ glUniform1d(this->uniforms[name], v); }
	inline void Set(char * name, glm::vec3 v){ glUniform3f(this->uniforms[name], v.x, v.y, v.z); }
	inline void Set(char * name, GLfloat x, GLfloat y, GLfloat z){ glUniform3f(this->uniforms[name], x, y, z); }
	inline void Set(char * name, glm::vec3 * v, GLuint n){ glUniform3fv(this->uniforms[name], n, (const GLfloat*)&v[0]); }
	inline void Set(char * name, glm::vec4 v){ glUniform4f(this->uniforms[name], v.x, v.y, v.z, v.w); }
	inline void Set(char * name, GLfloat x, GLfloat y, GLfloat z, GLfloat w){ glUniform4f(this->uniforms[name], x, y, z, w); }
	inline void Set(char * name, glm::mat4 v){ glUniformMatrix4fv(this->uniforms[name], 1, GL_FALSE, &v[0][0]); }
	inline void Set(char * name, granny_matrix_4x4 * v, GLuint n){ glUniformMatrix4fv(this->uniforms[name], n, GL_FALSE, (GLfloat *)v); }



	//Debug stuff


	inline void Print(char * name){ printf("%i\n", this->uniforms[name]); }


};





#endif
