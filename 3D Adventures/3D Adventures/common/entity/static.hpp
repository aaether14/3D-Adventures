#ifndef STATIC_HPP
#define STATIC_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.h>
#include <entity_info/static_info.hpp>
#include "palette/entity_palette.hpp"








class StaticManager


{




	void RenderPatch(Controller*ctrl, MeshShader * shader, std::vector<StaticEntityInfo*> patch_info);
	void RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node);


	EntityPalette * palette;



public:


	inline ~StaticManager(){ this->Clean(); }
	inline StaticManager(Controller * ctrl){ this->Init(ctrl); }
	void Init(Controller * ctrl);
	void Clean();


	void Render(Controller *ctrl, MeshShader * shader);


	inline EntityPalette*GetPalette(){ return this->palette; }
	

};





#endif