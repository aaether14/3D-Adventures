/*


Some useful math functions for matrix transformations


*/




#ifndef MATH_HELPER
#define MATH_HELPER





#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <util/view.hpp>
#include <stdio.h>
#include <string>
#include <sstream>
#include <granny.h>





#define LERP(a,b,c)  (((b) - (a)) * (c) + (a))
#define COUNT_OF(x) ((sizeof(x) / sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))





namespace Math
{




class Rectangle
{


public:



	glm::vec2 point;
	GLfloat width, height;


};





class Circle
{




public:



	glm::vec2 point;
	GLfloat radius;




};






	bool CircleRectangleCollision(Rectangle *rect, Circle * circ);
	GLuint SphereInFrustum(Frustum *frustum, glm::vec3 pos, GLfloat radius);



	glm::mat4 Translation(glm::vec3 t_vec);
	inline glm::mat4 Translation(GLfloat x, GLfloat y, GLfloat z){ return Translation(glm::vec3(x, y, z)); }


	glm::mat4 Scale(glm::vec3 t_vec);
	inline glm::mat4 Scale(GLfloat x, GLfloat y, GLfloat z){ return Scale(glm::vec3(x, y, z)); }
	inline glm::mat4 Scale(GLfloat v) { return Scale(v, v, v); }


	inline glm::mat4 Rotate(GLfloat x, GLfloat y, GLfloat z){ return glm::mat4_cast(glm::fquat(glm::vec3(x, y, z))); }
	inline glm::mat4 Rotate(glm::vec3 v){ return Rotate(v.x, v.y, v.z); }



	void print_matrix(glm::mat4 m);
	void print_vec3(glm::vec3 v);
	void print_ivec2(glm::ivec2 v);



	glm::mat4 ConvertGrannyMatrix(granny_matrix_4x4 gr);
	inline GLfloat randomf(GLfloat LO, GLfloat HI){ return LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO))); }


	glm::vec3 GetVecFromString(std::string str);
	std::string GetStringFromVec(glm::vec3 v);


}




#endif