#ifndef STATIC_INFO_HPP
#define STATIC_INFO_HPP



#include <components/model_component.hpp>
#include <camera_implementation/camera.hpp>
#include <util/view.hpp>
#include "uniform.hpp"
#include "../technique.hpp"
#include "../resource_loader.hpp"




#define GRANNY_MODEL 0
#define AAETHER_MODEL 1






class StaticEntity
{



	std::map<std::string, AComponent*> components;




public:





	void Render(ViewInfo * info, View * view, 
		ResourceLoader * res,Techniques * tech, 
		MeshShader *shader, glm::mat4 matrix);



	inline void AddComponent(std::string name, AComponent *comp){ components[name] = comp; }
	inline AComponent*GetComponent(std::string name){ return components[name]; }
	inline GLuint GetComponentsSize(){ return components.size(); }





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












