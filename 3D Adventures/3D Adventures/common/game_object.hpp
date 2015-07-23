#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP





#include <terrain/quad_tree.hpp>
#include <settings/settings.hpp>
#include "resource_loader.hpp"
#include "technique.hpp"





class GameObject
{



	QuadTree *q_tree;
	ResourceLoader * res;
	Techniques * techniques;




public:



	inline GameObject(GLuint window_width, GLuint window_height){ this->Init(window_width, window_height); }
	void Init(GLuint window_width, GLuint window_height);



	inline ~GameObject(){ this->Clean(); }
	void Clean();



	inline Techniques * GetTechniques(){ return this->techniques; }
	inline ResourceLoader* GetResource(){ return this->res; }
	inline QuadTree *GetTree(){ return this->q_tree; }


	inline void SetTree(QuadTree *q_tree){ this->q_tree = q_tree; }
	GLuint GetInd(glm::vec3 pos);


};


#endif