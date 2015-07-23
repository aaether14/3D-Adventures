#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.hpp>
#include <entity_info/transform_info.hpp>
#include "palette/entity_palette.hpp"







/**


Entity manager implementation to determine how each visible entity affects the scene
Also stores the entity palette
It uses the terrain quad tree for frustum culling


*/
class EntityManager


{



	/**
	Render entities bound to a patch
	*/
	void RenderPatch(Controller*ctrl, MeshShader * shader, std::vector<TransformInfo*> patch_info);
	/**
	Check quad against frustum in order to render frustum-visible entities
	*/
	void RenderQuad(Controller*ctrl, MeshShader * shader, QuadNode * node);


	EntityPalette * palette;



public:





	/**
	Calls Init()
	*/
	inline EntityManager(Controller * ctrl){ Init(ctrl); }
	/**
	Initialize data
	*/
	void Init(Controller * ctrl);



	/**
	Calls Clean()
	*/
	inline ~EntityManager(){ Clean(); }
	/**
	Clean data
	*/
	void Clean();


	/**
	Try to render entities
	*/
	void Render(Controller *ctrl, MeshShader * shader);
	/**
	Get pointer to palette
	*/
	inline EntityPalette*GetPalette(){ return this->palette; }
	

};





#endif