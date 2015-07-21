/*


Storing transform data for entity instancing


*/




#ifndef TRANSFORM_INFO_HPP
#define TRANSFORM_INFO_HPP



#include <entity/entity.hpp>








class TransformInfo
{



public:

    


	std::string entity_name;
	glm::mat4 matrix;


	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;




	void Render(ViewInfo * info, View * view,
		ResourceLoader * res, Techniques * tech,
		MeshShader *shader, Entity * entity);


};

















#endif












