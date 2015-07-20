/*



Entity data is stored here



*/





#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP




#include <entity_info/transform_info.hpp>
#include <base/base_state_saver.hpp>
#include <components/model_component.hpp>
#include <components/general_entity_info_component.hpp>




#define OBJECT_FOLDER "data\\objects\\"




class SceneInfo : public AStateSaver
{


private:



	std::vector<TransformInfo*> * entity_infos;
	GLuint number_of_tiles;
	glm::vec2 map_size;


	std::vector<Entity*>entities;


public:



	void Load();
	void Save();
	void Reset();



	inline std::vector<TransformInfo*> * GetEntityInfos(){ return entity_infos; }
	inline std::vector<Entity*> GetEntities(){ return entities; }




};




#endif