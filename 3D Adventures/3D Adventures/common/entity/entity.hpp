/*


Entity implmentation
Stores components


*/



#ifndef ENTITY_HPP
#define ENTITY_HPP




#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>
#include <camera_implementation/camera.hpp>
#include <util/view.hpp>
#include <mesh_shader.hpp>
#include "../technique.hpp"
#include "../resource_loader.hpp"







class Entity
{



	std::map<std::string, AComponent*> components;




public:





	void Render(ViewInfo * info, View * view,
		ResourceLoader * res, Techniques * tech,
		MeshShader *shader, glm::mat4 matrix);



	inline void AddComponent(std::string name, AComponent *comp){ components[name] = comp; }
	inline AComponent*GetComponent(std::string name){ return components[name]; }
	inline GLuint GetComponentsSize(){ return components.size(); }





	inline ~Entity(){ this->Clean(); }
	void Clean();


};






#endif
