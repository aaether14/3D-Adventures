#ifndef TERRAIN_HPP
#define TERRAIN_HPP




#include <texture/texture.hpp>
#include "terrain_strip.hpp"
#include <util/view.hpp>
#include <util/controller_math.hpp>
#include "quad_tree.hpp"
#include <terrain_shader.hpp>




#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))



#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define TANGENT_LOCATION     3



#define BASE_DIR "data/terrain_textures/"






class Terrain
{

	enum VB_TYPES {
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		TANGENT_VB,
		NUM_VBs
	};



	GLuint colormap_tex, texture_array, normal_texture_array;
	TerrainShader::TextureAttributes * tex_data;

	GLuint WIDTH, HEIGHT;
	GLfloat *heightField, fSizeX, fSizeZ;
	GLuint num_chunks;
	GLuint chunk_rows, chunk_cols;

	QuadTree * q_tree;
	GLuint max_mips;

	TerrainShader * shader;

	void RenderQuad(Frustum * frustum, QuadNode * node);



public:


	inline Terrain(TerrainShader * shader) { this->Init(shader); }
	inline ~Terrain() { this->Clean(); }


	void Init(TerrainShader * shader);
	void Clean();


	inline GLint Width(){ return this->WIDTH; }
	inline GLint Height(){ return this->HEIGHT; }
	inline GLfloat ScaleX(){ return this->fSizeX; }
	inline GLfloat ScaleZ(){ return this->fSizeZ; }



	inline QuadTree * GetTree(){ return this->q_tree; }


	inline GLfloat getHeight(GLint x, GLint z) { return heightField[z*WIDTH + x]; }


	void LoadColorFiles(char*tile_path, char*texture_set_path, char*normal_set_path,
		char* texture_attributes_set);


	void CreateTerra(char *path, 
		char*ch1,
		GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
		GLuint chunk_height, GLuint chunk_width,
		GLuint mipmaps);


	void Render(Frustum * frustum, bool wired = false);



	void SaveChunks(char * path,
		BYTE * bits,
		GLfloat fSizeX, GLfloat fSizeZ, GLfloat fSizeY1,
		GLuint chunk_height, GLuint chunk_width,
		GLuint height, GLuint width,
		GLuint mipmaps
		);


	void LoadChunks(char * path);
};


GLfloat HeightAt(Terrain*terrain, GLfloat x, GLfloat z);


#endif