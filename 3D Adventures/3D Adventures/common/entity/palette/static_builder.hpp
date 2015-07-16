#ifndef STATIC_BUILDER_HPP
#define STATIC_BUILDER_HPP





#include "../static_info.hpp"
#include "../ui/scene_outliner.hpp"
#include "../ui/ui_transform.hpp"
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>







class StaticBuilder
{


public:



	void Create(char*path);


	void Save(char*path,
		StaticEntity**entity, GLuint e_n,
		std::vector<StaticEntityInfo*>*entity_info,
		GLuint quad_width,
		GLuint quad_height);


};




class StaticPalette
{


	ui_Scene * ui_scene;
	ui_Transform * ui_transform;





	StaticEntity**entity;
	std::vector<StaticEntityInfo*>*entity_info;
	GLboolean visible;




	void Init();



	GLuint number_of_entities, id;
	GLint switch_id;
	StaticBuilder * builder;
	GLuint quad_width, quad_height;




public:


	inline ~StaticPalette(){ delete this->builder;  }
	inline StaticBuilder * GetBuilder(){ return this->builder; }
	inline ui_Scene * GetSceneOutliner(){ return this->ui_scene; }
	inline void SetWidth(GLuint quad_width){ this->quad_width = quad_width; }
	inline void SetHeight(GLuint quad_height){ this->quad_height = quad_height; }


	inline GLuint GetWidth(){ return this->quad_width; }
	inline GLuint GetHeight(){ return this->quad_height; }




	inline StaticPalette(){ this->Init(); }
	inline GLuint GetEntityNumber(){ return number_of_entities; }
	inline StaticEntity**GetEntity(){ return this->entity; }
	inline std::vector<StaticEntityInfo*>*GetEntityInfo(){ return this->entity_info; }


	glm::mat4 GetMatrix(GLboolean model_type, GLuint special);
	void Render(Controller*ctrl, MeshShader *u_data, StaticEntity ** entity);
	void ControlPalette(Controller * ctrl);
	void PlacePalette(Controller * ctrl, std::vector<StaticEntityInfo*>*entity_info, StaticEntity **entity);


	void SetNumbers(GLuint e_n);
	inline void SetDataPointers(StaticEntity**entity, std::vector<StaticEntityInfo*>*entity_info){ this->entity = entity; this->entity_info = entity_info; }



};


#endif