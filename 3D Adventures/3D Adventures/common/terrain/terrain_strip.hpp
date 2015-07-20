/*


Used to store terrain chunks


*/



#ifndef TERRAIN_STRIP_HPP
#define TERRAIN_STRIP_HPP




#include <gl/glew.h>
#include "texture/texture.hpp"
#include <util/math_helper.hpp>





#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))
#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define TANGENT_LOCATION     3



	class TerrainStrip
	{

		enum VB_TYPES {
			INDEX_BUFFER,
			POS_VB,
			NORMAL_VB,
			TEXCOORD_VB,
			TANGENT_VB,
			NUM_VBs
		};


		GLuint m_VAO;
		GLuint m_Buffers[NUM_VBs];
		GLuint width, height;

     

		GLuint mipmaps;
		GLuint *mip_start_buffer;
		GLuint *mip_count_buffer;


	public:


		void Init();
		void Clear();


		inline TerrainStrip() { this->Init(); }
		inline ~TerrainStrip(){ this->Clear(); }




		void Render(GLuint lod);


		void Create(GLuint strip_width, GLuint strip_height,
			glm::vec3 * heightData,
			glm::vec2 * uvData,
			glm::vec3 * normalData,
			glm::vec3 * tangentData,
			GLuint *index_buffer,
			GLuint index_size,
			GLuint *mip_start_buffer,
			GLuint *mip_count_buffer,
			GLuint mipmaps
			);


	};

	

#endif