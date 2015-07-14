#ifndef STATIC_BUILDER_HPP
#define STATIC_BUILDER_HPP





#include "static_info.hpp"
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


	bool SaveEntities(const CEGUI::EventArgs &args);
	inline bool UndoLastMove(const CEGUI::EventArgs &args)
	{
		DeleteLast();
		return 1;
	}



	StaticEntity**entity;
	std::vector<StaticEntityInfo*>*entity_info;
	GLboolean visible;


	void Init();



	GLuint number_of_entities, id;
	GLint switch_id;
	StaticBuilder * builder;
	GLuint quad_width, quad_height;
	std::vector<GLuint> moves;


	void SaveEntities();



public:


	inline ~StaticPalette(){ delete this->builder;  }
	inline StaticBuilder * GetBuilder(){ return this->builder; }
	inline void SetWidth(GLuint quad_width){ this->quad_width = quad_width; }
	inline void SetHeight(GLuint quad_height){ this->quad_height = quad_height; }


	inline GLuint GetWidth(){ return this->quad_width; }
	inline GLuint GetHeight(){ return this->quad_height; }


	struct PaletteInfo
	{

		GLuint ind;
		GLfloat scale;
		GLfloat scale_range;
		GLfloat scale_compute;
		glm::vec3 rot;
		GLfloat y_rot_range;
		GLfloat y_rot_compute;
		glm::vec3 pos;
		std::string file_name;


	}p_info;


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
	void DeleteLast();



};


#endif