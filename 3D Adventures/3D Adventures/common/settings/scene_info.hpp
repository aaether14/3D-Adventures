#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP





#include <base/base_state_saver.hpp>
#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>
#include <entity/entity.hpp>
#include <entity_instance/entity_instance.hpp>
#include <converter/assimp_converter.hpp>




#define OBJECT_FOLDER "data\\objects\\"





/**



Entity data is stored here



*/
class SceneInfo : public AStateSaver
{


private:



	///////Subject to change///////////


	/*
	Instance information
	*/
	std::vector<EntityInstance*> * entity_instances;



	GLuint number_of_tiles;
	glm::vec2 map_size;


    //////////////////////////////////




	std::map<std::string, boost::shared_ptr<Entity>> entity_map;
	/**
	Based on the files in path you provide ScenInfo adds specific components to the given entity
	*/
	void AddComponentsToEntity(char * path, Entity * new_entity);
	/**
	Adds entity to the entity map
	*/
	void AddEntity(Entity* new_entity);



public:

	
	/**
	Sets path of the file the class will affect
	*/
	inline SceneInfo(char * path){ SetPath(path); }




	/**
	Load data from file
	*/
	void Load();
	/**
	Save data to file
	*/
	void Save();
	/**
	Reset data
	*/
	void Reset();








	/**
	Get vector of entity instances
	*/
	std::vector<EntityInstance*> * GetEntityInstances(){ return entity_instances; }








	/**
	Get entity with provided key
	*/
	inline Entity* GetEntity(std::string name){ return entity_map[name].get(); }
	/**
	Get entity with provided index
	*/
	inline Entity* GetEntity(GLuint counter){ std::map<std::string, boost::shared_ptr<Entity>>::iterator it(entity_map.begin()); std::advance(it, counter); return it->second.get(); }
	/**
	Get number of entities in map
	*/
	inline GLuint GetNumberOfEntities(){ return entity_map.size(); }

	/**
	Insert new entity from given folder
	*/
	void InsertNewEntity(std::string path);


};




#endif