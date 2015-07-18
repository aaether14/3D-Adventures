#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP




#include <entity_info/static_info.hpp>
#include <base/base_state_saver.hpp>
#include <components/model_component.hpp>





#define OBJECT_FOLDER "data\\objects\\"




class SceneInfo : public AStateSaver
{


private:

	std::vector<StaticEntityInfo*> * entity_infos;
	std::vector<StaticEntity*>entities;


public:



	void Load();
	void Save();
	void Reset();



	inline std::vector<StaticEntityInfo*> * GetEntityInfos(){ return entity_infos; }
	inline std::vector<StaticEntity*> GetEntities(){ return entities; }


	inline void ReserveInfoSpace(GLuint size){ entity_infos = new std::vector<StaticEntityInfo*>[size]; }


};




#endif