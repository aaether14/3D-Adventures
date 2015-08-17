#ifndef TRANSFORM_INFO_HPP
#define TRANSFORM_INFO_HPP




#include <util/string_helper.hpp>
#include <util/math_helper.hpp>




/**


Storing transform data for entity instancing


*/
class TransformInfo
{



public:

    


	std::string entity_name;
	glm::mat4 matrix;


	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;





	/**
	Call Clean()
	*/
	inline TransformInfo(){}



};

















#endif












