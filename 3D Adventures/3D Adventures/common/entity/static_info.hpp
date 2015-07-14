#ifndef STATIC_INFO_HPP
#define STATIC_INFO_HPP




#include <model_loaders/granny_loader.h>
#include "controls.hpp"
#include <util/controller_math.hpp>
#include  <fstream>
#include "uniform.hpp"
#include <model_loaders/aaether_loader.hpp>





#define GRANNY_MODEL 0
#define AAETHER_MODEL 1






class StaticEntity
{




	GLuint type;
	std::string path;
	GrannyModel * gr_model;
	Aa_model * aa_model;




public:




	void Render(Controller *ctrl, MeshShader *u_data, glm::mat4 matrix);
	inline void SetPath(std::string path){ this->path = path; }
	inline void SetType(GLuint type){ this->type = type; }
	inline std::string GetPath(){ return this->path; }
	inline GLuint GetType(){ return this->type; }
	inline GrannyModel* GetGranny(){ return this->gr_model; }
	inline void SetGranny(GrannyModel * gr_model){ this->gr_model = gr_model; }
	inline void SetAaether(Aa_model * aa_model){ this->aa_model = aa_model; }
	inline Aa_model * GetAaether(){ return this->aa_model; }
	inline ~StaticEntity(){ this->Clean(); }
	void Clean();


};



class StaticEntityInfo


{



	GLuint id;
	glm::mat4 matrix;




public:


	inline void SetMatrix(glm::mat4 matrix){ this->matrix = matrix; }
	inline void SetId(GLuint id){ this->id = id; }
	inline GLuint GetId(){ return this->id; }
	inline glm::mat4 GetMatrix(){ return this->matrix; }
	void Render(Controller*ctrl, MeshShader *u_data, StaticEntity ** entity);


};

















#endif












