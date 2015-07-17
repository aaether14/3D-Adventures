#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP





#include <util/controller_math.hpp>
#include <util/file_helper.hpp>
#include "../base//base_state_saver.hpp"







class Environment : public AStateSaver
{


		

public:




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



	inline Environment(char * path){ this->Init(path); }
	void Init(char * path);

	

	void Reset();
	void Save();
	void Load();


};



#endif