#ifndef STATIC_HPP
#define STATIC_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.h>
#include "static_info.hpp"
#include "palette/static_builder.hpp"






template<typename T>
void destroy_vector(std::vector<T*> &v)
{
	while (!v.empty()) {
		delete v.back();
		v.pop_back();
	}
}




class StaticManager


{



	StaticEntity ** entity;
	GLuint e_n, quad_width, quad_height;
	std::vector<StaticEntityInfo*> *entity_info;



	void RenderPatch(Controller*ctrl, MeshShader * shader, std::vector<StaticEntityInfo*> patch_info);
	void RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node);


	StaticPalette * palette;



public:


	inline ~StaticManager(){ this->Clean(); }
	inline StaticManager(Controller * ctrl){ this->Init(ctrl); }
	void Init(Controller * ctrl);
	void Clean();


	void Load(char *path, Controller * ctrl);
	void Render(Controller *ctrl, MeshShader * shader);


	inline StaticPalette*GetPalette(){ return this->palette; }
	inline std::vector<StaticEntityInfo*> * GetEntityInfos(){ return entity_info; }
	inline StaticEntity ** GetEntities(){ return entity; }
	

};





#endif