#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP





#include <util/controller_math.hpp>
#include <util/file_helper.hpp>







class Environment
{


		

public:



	std::string file_name;




	glm::vec3 sun_dir;
	glm::vec3 sun_color;
	glm::vec3 fog_color;


	GLfloat model_ambient;
	GLfloat terrain_ambient;
	GLfloat model_diffuse;
	GLfloat terrain_diffuse;
	GLfloat model_bright;
	GLfloat terrain_bright;
	GLfloat fog_density;



	GLboolean should_reset;


	inline Environment(){ this->Init(); }
	void Init();

	



	void Reset();
	void Save(char*path);
	void Load(char*path);


};



#endif