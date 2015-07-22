#ifndef TRANSFORM_INFO_HPP
#define TRANSFORM_INFO_HPP




#include <entity/entity.hpp>







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
	Render current instance of entity with provided info
	*/
	void Render(ViewInfo * info, View * view,
		ResourceLoader * res, Techniques * tech,
		MeshShader *shader, Entity * entity);




	/**
	Call Clean()
	*/
	inline TransformInfo(){ Clean(); }
	/**
	Cleans data
	*/
	void Clean();



};

















#endif












