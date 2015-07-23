#ifndef QUAD_TREE
#define QUAD_TREE





#include <gl/glew.h>
#include "texture/texture.hpp"
#include "terrain_strip.hpp"
#include <fstream>





/**

Quad tree implementation


*/
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
	

	/**
	Get center of node
	*/
	inline glm::vec3 GetCenter(){ return this->center; }
	/**
	Get radius of node
	*/
	inline GLfloat GetRadius(){ return this->radius; }
	/**
	Get index of node
	*/
	inline GLuint GetInd(){ return this->ind; }

	
	/**
	Set if quad node should be visible
	*/
	inline void SetVisible(GLboolean visible){ this->visible = visible; }
	/**
	Query node visibility
	*/
	inline GLboolean GetVisible(){ return this->visible; }


	/**
	Get child nodes
	*/
	inline QuadNode ** GetNodes(){ return this->nodes; }
	/**
	Pointer to node's TerrainStrip (if terminal node, otherwise NULL)
	*/
	inline TerrainStrip *GetChunk(){return this->chunk;}
	/**
	Set parent of node
	*/
	inline void SetParent(QuadNode *p){ this->parent = p; }



	/**
	Create out of 4 points and chunk_height and chunk_width to see where to stop splitting
	*/
	void Create(glm::ivec2 sq_points[4], GLuint chunk_height, GLuint chunk_width,
		GLuint width,
		glm::vec3 *heightData);



	/**
	Save quad node to file
	*/
	void Save(std::ofstream *fout, GLuint width, GLuint chunk_height, GLuint chunk_width,
		glm::vec3 *heightData,
		glm::vec2 *uvData,
		glm::vec3 *normalData,
		glm::vec3 *tangentData,
		GLfloat min_x,
		GLfloat min_z);




	/**
	Load quad node from file
	*/
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



	/**
	Read info for node
	*/
	void Read();
	/**
	Cleans data
	*/
	void Clean();


	/**
	Calls Clean()
	*/
	inline ~QuadNode(){ Clean(); }


};


class QuadTree
{




	QuadNode * start_node;



	GLuint tree_width, tree_height;
	GLfloat min_x, min_z;




public:


	/**
	Get width of a chunk
	*/
	inline GLfloat GetMinX(){ return this->min_x; }
	/**
	Get height of a chunk
	*/
	inline GLfloat GetMinZ(){ return this->min_z; }


	/**
	Pointer to starting node
	*/
	inline QuadNode* GetStartNode() { return this->start_node; }


	/**
	Get width (number of chunks)
	*/
	inline GLuint GetWidth(){ return this->tree_width; }
	/**
	Get height (number of chunks)
	*/
	inline GLuint GetHeight(){ return this->tree_height; }



	/**
	Initialize starting node
	*/
	inline QuadTree(){ this->start_node = new QuadNode(); this->start_node->SetParent(NULL); }
	/**
	Recursive delete of all nodes
	*/
	inline ~QuadTree(){ delete this->start_node; }





	/**
	Create tree 
	*/
	void Create(GLuint quad_height, GLuint quad_width,
		GLuint chunk_height, GLuint chunk_width,
		GLuint width,
		glm::vec3 *heightData);




	/**
	Save tree to file*/
	void Save(std::ofstream *fout,GLuint width,GLuint chunk_height,GLuint chunk_width,
		glm::vec3 *heightData,
		glm::vec2 *uvData,
		glm::vec3 *normalData,
		glm::vec3 *tangentData,
		GLfloat min_x,
		GLfloat min_z);



	/**
	Load tree from file
	*/
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




