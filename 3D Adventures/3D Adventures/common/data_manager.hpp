#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP




#include <controller/controls_source.hpp>
#include <terrain/quad_tree.hpp>
#include <settings/settings.hpp>
#include <base/base_module.hpp>
#include "resource_loader.hpp"
#include "technique.hpp"





/**
Controls the scene resources and the filters pack
*/
class DataManager : public AModule
{



	QuadTree *q_tree;
	ResourceLoader * res;
	Techniques * techniques;




public:



	/**
	Initializes with screen size
	*/
	void Init();
	/**
	Handles drag&drop entity adition
	*/
	void Enable();




	/**
	Cleans data
	*/
	void Clean();



	/**
	Get pointer to filter pack Techniques
	*/
	inline Techniques * GetTechniques(){ return this->techniques; }
	/**
	Get pointer to Resource Loader
	*/
	inline ResourceLoader* GetResource(){ return this->res; }
	/**
	Get pointer to terrain quad tree
	*/
	inline QuadTree *GetTree(){ return this->q_tree; }

	/**
	Set terrain quad tree
	*/
	inline void SetTree(QuadTree *q_tree){ this->q_tree = q_tree; }
	/**
	Get index of terrain at 'pos'
	*/
	GLuint GetInd(glm::vec3 pos);


};


#endif