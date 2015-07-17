#ifndef STATIC_INFO_HPP
#define STATIC_INFO_HPP




#include <base/base_model_loader.hpp>
#include <camera_implementation/camera.hpp>
#include <util/view.hpp>
#include "uniform.hpp"
#include "../technique.hpp"
#include "../resource_loader.hpp"




#define GRANNY_MODEL 0
#define AAETHER_MODEL 1






class StaticEntity
{




	GLuint type;
	std::vector<AModel*>model_components;




public:




	void Render(ViewInfo * info, View * view, 
		ResourceLoader * res,Techniques * tech, 
		MeshShader *shader, glm::mat4 matrix);

	inline void AddModelComponent(AModel* model_component){ model_components.push_back(model_component); }



	inline void SetType(GLuint type){ this->type = type; }
	inline GLuint GetType(){ return this->type; }




	inline ~StaticEntity(){ this->Clean(); }
	void Clean();


};



class StaticEntityInfo


{



	GLuint id;
	glm::mat4 matrix;




public:



	inline void SetId(GLuint id){ this->id = id; }
	inline GLuint GetId(){ return this->id; }


	inline glm::mat4 GetMatrix(){ return this->matrix; }
	inline void SetMatrix(glm::mat4 matrix){ this->matrix = matrix; }


	void Render(ViewInfo * info, View * view,
		ResourceLoader * res, Techniques * tech,
		MeshShader *shader, std::vector<StaticEntity*>entities);


};

















#endif












