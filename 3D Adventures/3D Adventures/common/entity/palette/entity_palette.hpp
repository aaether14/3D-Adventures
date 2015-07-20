/*


entity palette implementation
also stores information affecting scene outliner and transform tab from ui


*/




#ifndef STATIC_BUILDER_HPP
#define STATIC_BUILDER_HPP





#include <entity_info/transform_info.hpp>
#include "../ui/scene_outliner.hpp"
#include "../ui/ui_transform.hpp"
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>






class EntityPalette
{


	//UI data

	ui_Scene * ui_scene;
	ui_Transform * ui_transform;



	GLboolean visible;
	GLuint id;




	void Init();





public:



	inline ui_Scene * GetSceneOutliner(){ return this->ui_scene; }



	inline EntityPalette(){ this->Init(); }


	glm::mat4 GetMatrix(Entity * entity);
	void Render(Controller*ctrl, MeshShader *u_data);
	void ControlPalette(Controller * ctrl);
	void PlacePalette(Controller * ctrl);




};


#endif