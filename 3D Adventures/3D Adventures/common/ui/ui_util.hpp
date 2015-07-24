#ifndef UI_UTIL_HPP
#define UI_UTIL_HPP





#include <glfw3.h>
#include <util/math_helper.hpp>
#include <CEGUI/CEGUI.h>





/**


Some functions to connect CEGUI to the other libraries


*/
namespace UI_UTIL
{


	/**
	Convert key codes from a library to another
	*/
	CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey);
	/**
	Convert mouse codes from a library to another
	*/
	CEGUI::MouseButton GlfwToCeguiMouseButton(int glfwButton);
	/**
	Convert colour from a library to another
	*/
	inline CEGUI::Colour GetCEGUIColour(glm::vec4 c){ return CEGUI::Colour(c.x, c.y, c.z, c.w); }
	/**
	Convert colour from a library to another
	*/
	inline CEGUI::Colour GetCEGUIColour(glm::vec3 c){ return GetCEGUIColour(glm::vec4(c, 1.0)); }
	/**
	Convert colour from a library to another
	*/
	inline glm::vec4 GetGLMColour(CEGUI::Colour c){ return glm::vec4(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()); }


}


#endif