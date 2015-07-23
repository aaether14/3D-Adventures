#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP




#include <entity_info/transform_info.hpp>
#include <base/base_state_saver.hpp>
#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>
#include <converter/assimp_converter.hpp>




#define OBJECT_FOLDER "data\\objects\\"





/**



Entity data is stored here



*/
class SceneInfo : public AStateSaver
{


private:


	/*
	Instance information
	*/
	std::vector<TransformInfo*> * entity_infos;



	GLuint number_of_tiles;
	glm::vec2 map_size;


	std::map<std::string, Entity*> entity_map;
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
	inline std::vector<TransformInfo*> * GetEntityInfos(){ return entity_infos; }
	/**
	Get entity with provided key
	*/
	inline Entity* GetEntity(std::string name){ return entity_map[name]; }
	/**
	Get entity with provided index
	*/
	inline Entity* GetEntity(GLuint counter){ std::map<std::string, Entity*>::iterator it(entity_map.begin()); std::advance(it, counter); return it->second; }
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