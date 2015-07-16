#ifndef CONTROLS_SOURCE_HPP
#define CONTROLS_SOURCE_HPP




#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ui/ui_util.hpp>





typedef char GLchar;




class FPS
{


	GLfloat fps;
	GLint frames;
	GLdouble lastTime;
	GLdouble lastTime2;
	GLdouble deltaTime, returnable_deltaTime;




public:




	inline GLfloat Get() { return fps; }
	inline GLdouble Delta() { return this->returnable_deltaTime; }
	void FirstPass();
	void Compute();



};



class ControllerSource
{


	static GLFWwindow* window;



	static GLint window_width, window_height;
	static GLboolean fullscreen;
	static GLchar * title;
	static GLuint opengl_major_version;
	static GLuint opengl_minor_version;


	//---


	FPS * fps;




	static GLvoid key_callback(GLFWwindow* window, GLint key, GLint scancode, GLint action, GLint mods);
	static GLvoid char_callback(GLFWwindow * window, GLuint code);
	static GLuint keys[512];
	static GLuint fullscreen_key;



	static GLvoid mouse_callback(GLFWwindow* window, GLint button, GLint action, GLint mods);
	static glm::vec2 mouse_position;
	static GLuint mouse_buttons[8];


	static GLvoid cursor_callback(GLFWwindow* window, GLdouble x, GLdouble y);
	static GLvoid resize_callback(GLFWwindow* window, GLint width, GLint height);
	static GLvoid scroll_callback(GLFWwindow* window, GLdouble xoffset, GLdouble yoffset);
	static GLdouble wheel_offset;




	static void InitCallbacks();




public:



	inline GLuint GetKey(GLuint code){ return ControllerSource::keys[code]; }
	inline GLuint GetKeyOnce(GLuint code){ GLuint result = (ControllerSource::keys[code] == 1); if (result)ControllerSource::keys[code]++; return result; }


	inline glm::vec2 GetMousePosition(){ return ControllerSource::mouse_position; }
	inline GLuint GetMouseButton(GLuint code){ return ControllerSource::mouse_buttons[code]; }
	inline GLuint GetMouseButtonOnce(GLuint code){ GLuint result = (ControllerSource::mouse_buttons[code] == 1); if (result)ControllerSource::mouse_buttons[code]++; return result; }
	inline GLdouble GetWheelOffset(){ return wheel_offset; }
	inline GLvoid ResetWheelOffset(){ wheel_offset = 0.0; }


	inline FPS*GetFpsPointer(){ return this->fps; }
	inline glm::ivec2 GetWindowSize() { return glm::ivec2(this->window_width, this->window_height); }
	inline GLint GetWindowWidth(){ return this->window_width; }
	inline GLint GetWindowHeight(){ return this->window_height; }
	inline void SetFullscreenKey(GLuint key){ this->ControllerSource::fullscreen_key = key; }
	inline GLFWwindow * GetWindow(){ return this->window; }


	inline ControllerSource() { this->Init(); }

	inline GLfloat returnFps(){ return this->fps->Get(); }


	static GLboolean CreateWindow(GLuint window_width, GLuint window_height,
		GLboolean fullscreen,
		char * title,
		GLuint opengl_major_version,
		GLuint opengl_minor_version);



	void Init();
	void Enable();




	void Clean();
	inline  ~ControllerSource(){ this->Clean(); }
	



};




#endif