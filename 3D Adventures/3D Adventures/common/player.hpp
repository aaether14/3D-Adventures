#ifndef PLAYER_HPP
#define PLAYER_HPP




#include <model_loaders/granny_loader.h>
#include "controls.hpp"
#include <util/controller_math.hpp>
#include  <fstream>
#include "uniform.hpp"
#include <model_loaders/aaether_loader.hpp>





#define NORMAL_MODEL 0
#define NEW_MODEL 1
#define NO_HELMET 2





class Player
{


	GrannyModel * player_model, *helmet, *weapon;
	GrannyModel * mount_model;
	Aa_model *cube;


	glm::mat4 player_cache, mount_cache;
	glm::mat4 player_matrix, weapon_matrix, mount_matrix;


	GLuint type;
	GLuint anim;
	GLfloat angle;



	void WriteCharCache(char *path, std::string*files, GLuint n, glm::mat4 cache, GLuint type);
	void WriteWeapCache(char *path, std::string*files);
	void WriteMountCache(char *path, std::string*files, GLuint n, glm::mat4 cache);


public:


	inline GLuint GetAnim(){ return this->anim; }
	inline ~Player() { this->Clean(); }
	void Clean();
	void Enable(Controller *ctrl);



	void SaveChar(char *path);
	void SaveWeap(char *path);
	void SaveMount(char *path);


	void LoadChar(char *path);
	void LoadWeap(char *path);
	void LoadMount(char *path);


	inline glm::mat4 GetCamera(){ return this->player_matrix; }
	inline glm::mat4 GetWeapCamera(){ return this->weapon_matrix; }
	inline glm::mat4 GetMountCamera(){ return this->mount_matrix; }



	void Render(Controller *ctrl, MeshShader * shader);
	void RenderCube(Controller *ctrl, MeshShader * shader);


};



#endif