#ifndef STATIC_BUILDER_HPP
#define STATIC_BUILDER_HPP





#include <entity_info/transform_info.hpp>
#include "../ui/scene_outliner.hpp"
#include "../ui/ui_transform_tab.hpp"
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>





/**


entity palette implementation
also stores information affecting scene outliner and transform tab from ui


*/
class EntityPalette
{


	//UI data

	ui_SceneOutliner * ui_scene_outliner;
	ui_TransformTab * ui_transform_tab;



	GLboolean visible;
	Entity * current_entity;
	GLuint entity_counter;



	/**
	Initialize data*/
	void Init();
	/**
	Cleans data
	*/
	void Clean();
	/**
	Compute Model matrix from entity information
	*/
	glm::mat4 GetMatrix(Entity * entity); 




public:


	/**
	Get pointer to scene outliner
	*/
	inline ui_SceneOutliner * GetSceneOutliner(){ return ui_scene_outliner; }
	/**
	Call Init
	*/
	inline EntityPalette(){ Init(); }
	/**
	Call Clean
	*/
	inline ~EntityPalette(){ Clean(); }

	/**
	Render the currently selected entity
	*/
	void Render(Controller*ctrl, MeshShader *u_data);
	/**
	Manage input
	*/
	void ControlPalette(Controller * ctrl);
	/**
	Entity placement
	*/
	void PlacePalette(Controller * ctrl);




};


#endif