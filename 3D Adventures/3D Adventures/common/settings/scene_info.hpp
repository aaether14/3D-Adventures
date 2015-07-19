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
	std::vector<Entity*>entities;


public:



	void Load();
	void Save();
	void Reset();



	inline std::vector<TransformInfo*> * GetEntityInfos(){ return entity_infos; }
	inline std::vector<Entity*> GetEntities(){ return entities; }


	inline void ReserveInfoSpace(GLuint size){ entity_infos = new std::vector<TransformInfo*>[size]; }


};




#endif