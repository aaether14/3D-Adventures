#ifndef SCENE_INFO_HPP
#define SCENE_INFO_HPP




#include <base/base_state_saver.hpp>
#include <entity/static_info.hpp>
#include <util/file_helper.hpp>
#include <util/string_helper.hpp>
#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.h>





#define OBJECT_FOLDER "data\\objects\\"




class SceneInfo : public AStateSaver
{


private:

	std::vector<std::vector<StaticEntityInfo*>> entity_infos;
	std::vector<StaticEntity*>entities;


public:



	void Load();
	void Save();
	void Reset();



	inline std::vector<std::vector<StaticEntityInfo*>> GetEntityInfos(){ return entity_infos; }
	inline std::vector<StaticEntity*> GetEntities(){ return entities; }



};




#endif