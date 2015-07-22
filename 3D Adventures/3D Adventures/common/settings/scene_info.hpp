/*



Entity data is stored here



*/





#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP




#include <entity_info/transform_info.hpp>
#include <base/base_state_saver.hpp>
#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>
#include <converter/assimp_converter.hpp>




#define OBJECT_FOLDER "data\\objects\\"




class SceneInfo : public AStateSaver
{


private:



	std::vector<TransformInfo*> * entity_infos;
	GLuint number_of_tiles;
	glm::vec2 map_size;


	std::map<std::string, Entity*> entity_map;
	void AddComponentsToEntity(char * path, Entity * new_entity);
	void AddEntity(Entity* new_entity);



public:

	
	inline SceneInfo(char * path){ SetPath(path); }


	void Load();
	void Save();
	void Reset();



	inline std::vector<TransformInfo*> * GetEntityInfos(){ return entity_infos; }
	inline Entity* GetEntity(std::string name){ return entity_map[name]; }
	inline Entity* GetEntity(GLuint counter){ std::map<std::string, Entity*>::iterator it(entity_map.begin()); std::advance(it, counter); return it->second; }
	inline GLuint GetNumberOfEntities(){ return entity_map.size(); }


	void InsertNewEntity(std::string path);


};




#endif