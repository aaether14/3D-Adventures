#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP





#include <terrain/quad_tree.hpp>
#include "resource_loader.hpp"
#include <filters/shadow_calculator.hpp>
#include "technique.hpp"
#include <settings/settings.hpp>





class GameObject
{



	QuadTree *q_tree;
	ShadowBBox * shadow_bbox;
	ResourceLoader * res;
	Techniques * techniques;
	Settings * settings;




public:



	inline GameObject(GLuint window_width, GLuint window_height){ this->Init(window_width, window_height); }
	void Init(GLuint window_width, GLuint window_height);



	inline ~GameObject(){ this->Clean(); }
	void Clean();



	inline Techniques * GetTechniques(){ return this->techniques; }
	inline ShadowBBox * GetShadowBBox(){ return this->shadow_bbox; }
	inline ResourceLoader* GetResource(){ return this->res; }
	inline QuadTree *GetTree(){ return this->q_tree; }
	inline Settings * GetSettings(){ return this->settings; }


	inline void SetTree(QuadTree *q_tree){ this->q_tree = q_tree; }
	GLuint GetInd(glm::vec3 pos);


};


#endif