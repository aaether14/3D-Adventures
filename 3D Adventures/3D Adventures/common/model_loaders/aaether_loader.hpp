#ifndef AAETHER_LOADER
#define AAETHER_LOADER



#include <util/string_helper.hpp>
#include "math_3d.h"
#include <texture/texture.hpp>
#include <assert.h>
#include <base/base_model_loader.hpp>





#define INVALID_MATERIAL 0xFFFFFFFF




class Aa_model : public AModel
{



	enum VB_TYPES
	{
		INDEX_BUFFER,
		POS_VB,
		NORMAL_VB,
		TEXCOORD_VB,
		BONE_VB,
		NUM_VBs
	};


	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];



	struct Aa_entry {
		Aa_entry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		GLuint NumIndices;
		GLuint BaseVertex;
		GLuint BaseIndex;
		GLuint MaterialIndex;
	};


	vector<Aa_entry> m_Entries;
	vector<GLuint> m_Textures;


public:


	Aa_model();
	~Aa_model();


	int Load(const char*path);
	void Render();
	void Clean();


};

#endif