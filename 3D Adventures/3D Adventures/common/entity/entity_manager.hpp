#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.hpp>
#include <entity_info/transform_info.hpp>
#include <data_manager.hpp>
#include <controls.hpp>
#include <base/base_module.hpp>







/**


Entity manager implementation to determine how each visible entity affects the scene
Also stores the entity palette
It uses the terrain quad tree for frustum culling


*/
class EntityManager : public AModule


{



	/**
	Render entities bound to a patch
	*/
	void RenderPatch(std::vector<TransformInfo*> patch_info);
	/**
	Check quad against frustum in order to render frustum-visible entities
	*/
	void RenderQuad(QuadNode * node);




public:




	/**
	Initialize data
	*/
	void Init();




	/**
	Clean data
	*/
	void Clean();


	/**
	Try to render entities
	*/
	void Enable();
	

};





#endif