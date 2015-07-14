#ifndef UI_UTIL_HPP
#define UI_UTIL_HPP





#include <glfw3.h>
#include <util/controller_math.hpp>
#include <CEGUI/CEGUI.h>




CEGUI::Key::Scan GlfwToCeguiKey(int glfwKey);
CEGUI::MouseButton GlfwToCeguiMouseButton(int glfwButton);
inline CEGUI::Colour GetCEGUIColour(glm::vec4 c){ return CEGUI::Colour(c.x, c.y, c.z, c.w); }
inline CEGUI::Colour GetCEGUIColour(glm::vec3 c){ return GetCEGUIColour(glm::vec4(c, 1.0)); }
inline glm::vec4 GetGLMColour(CEGUI::Colour c){ return glm::vec4(c.getRed(), c.getGreen(), c.getBlue(), c.getAlpha()); }




#endif