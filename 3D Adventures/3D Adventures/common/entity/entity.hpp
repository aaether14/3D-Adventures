#ifndef ENTITY_HPP
#define ENTITY_HPP




#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>
#include <base/base_module.hpp>



/**


Entity implmentation
Stores components


*/
class Entity
{



	std::map<std::string, AComponent*> components;




public:




	/**
	Render if components have required info
	*/
	void Render(AModule * manager, glm::mat4 matrix);



	/**
	Add a component to the entity
	*/
	inline void AddComponent(std::string name, AComponent *comp){ components[name] = comp; }
	/**
	Get component by key
	*/
	inline AComponent*GetComponent(std::string name){ return components[name]; }
	/**
	Get number of components
	*/
	inline GLuint GetComponentsSize(){ return components.size(); }




	/**
	Calls Clean()
	*/
	inline ~Entity(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


};






#endif
