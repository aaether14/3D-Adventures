#ifndef QUAD_TREE
#define QUAD_TREE


#include <gl/glew.h>
#include "texture/texture.hpp"
#include "terrain_strip.hpp"
#include <fstream>



class QuadNode
{


	glm::vec3 h_points[4];
	glm::vec3 center;
	GLfloat radius;


	GLuint ind;


	GLboolean visible;


	QuadNode ** nodes;



	QuadNode * parent;



	TerrainStrip * chunk;



public:
	

	inline glm::vec3 GetCenter(){ return this->center; }



	inline GLfloat GetRadius(){ return this->radius; }


	inline GLuint GetInd(){ return this->ind; }

	
	inline void SetVisible(GLboolean visible){ this->visible = visible; }


	inline GLboolean GetVisible(){ return this->visible; }



	inline QuadNode ** GetNodes(){ return this->nodes; }



	inline TerrainStrip *GetChunk(){return this->chunk;}



	inline void SetParent(QuadNode *p){ this->parent = p; }


	void Create(glm::ivec2 sq_points[4], GLuint chunk_height, GLuint chunk_width,
		GLuint width,
		glm::vec3 *heightData);





	void Save(std::ofstream *fout, GLuint width, GLuint chunk_height, GLuint chunk_width,
		glm::vec3 *heightData,
		glm::vec2 *uvData,
		glm::vec3 *normalData,
		glm::vec3 *tangentData,
		GLfloat min_x,
		GLfloat min_z);





	void Load(std::ifstream *fin,
		GLuint chunk_width, GLuint chunk_height,
		glm::vec3 * heightData,
		glm::vec2 * uvData,
		glm::vec3 * normalData,
		glm::vec3 * tangentData,
		GLuint *index_buffer,
		GLuint index_size,
		GLuint *mip_start_buffer,
		GLuint *mip_count_buffer,
		GLuint mipmaps,
		GLfloat min_x,
		GLfloat min_z);


	void Read();



	void Clean();


	inline ~QuadNode(){ this->Clean(); }


};


class QuadTree
{


	QuadNode * start_node;


	GLuint tree_width, tree_height;


	GLfloat min_x, min_z;


public:


	inline GLfloat GetMinX(){ return this->min_x; }



	inline GLfloat GetMinZ(){ return this->min_z; }


	inline QuadNode* GetStartNode() { return this->start_node; }


	inline GLuint GetWidth(){ return this->tree_width; }



	inline GLuint GetHeight(){ return this->tree_height; }



	inline QuadTree(){ this->start_node = new QuadNode(); this->start_node->SetParent(NULL); }



	inline ~QuadTree(){ delete this->start_node; }


	void Create(GLuint quad_height, GLuint quad_width,
		GLuint chunk_height, GLuint chunk_width,
		GLuint width,
		glm::vec3 *heightData);




	void Save(std::ofstream *fout,GLuint width,GLuint chunk_height,GLuint chunk_width,
		glm::vec3 *heightData,
		glm::vec2 *uvData,
		glm::vec3 *normalData,
		glm::vec3 *tangentData,
		GLfloat min_x,
		GLfloat min_z);

	void Load(std::ifstream *fin,
		GLuint chunk_width, GLuint chunk_height,
		glm::vec3 * heightData,
		glm::vec2 * uvData,
		glm::vec3 * normalData,
		glm::vec3 * tangentData,
		GLuint *index_buffer,
		GLuint index_size,
		GLuint *mip_start_buffer,
		GLuint *mip_count_buffer,
		GLuint mipmaps,
		GLfloat min_x,
		GLfloat min_z);


};





#endif




