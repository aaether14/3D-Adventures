/*


Entity manager implementation to determine how each visible entity affects the scene
Also stores the entity palette
It uses the terrain quad tree for frustum culling


*/



#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.h>
#include <entity_info/transform_info.hpp>
#include "palette/entity_palette.hpp"








class EntityManager


{




	void RenderPatch(Controller*ctrl, MeshShader * shader, std::vector<TransformInfo*> patch_info);
	void RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node);


	EntityPalette * palette;



public:


	inline ~EntityManager(){ this->Clean(); }
	inline EntityManager(Controller * ctrl){ this->Init(ctrl); }
	void Init(Controller * ctrl);
	void Clean();


	void Render(Controller *ctrl, MeshShader * shader);


	inline EntityPalette*GetPalette(){ return this->palette; }
	

};





#endif