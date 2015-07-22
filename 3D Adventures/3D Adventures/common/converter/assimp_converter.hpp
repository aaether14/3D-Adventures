#ifndef ASSIMP_CONVERTER_HPP
#define	ASSIMP_CONVERTER_HPP





#include <assimp/Importer.hpp>   
#include <assimp/scene.h>    
#include <assimp/postprocess.h> 
#include <assimp/Exporter.hpp>
#include <util/math_helper.hpp>
#include <util/file_helper.hpp>
#include <util/string_helper.hpp>




class AssimpConverter
{




public:


	bool ConvertModel(const std::string& Filename);


private:


	bool InitFromScene(const aiScene* pScene, const std::string& Filename);
	void InitMesh(GLuint MeshIndex,
		const aiMesh* paiMesh,
		std::vector<glm::vec3>& Positions,
		std::vector<glm::vec3>& Normals,
		std::vector<glm::vec2>& TexCoords,
		std::vector<GLuint>& Indices);





#define INVALID_MATERIAL 0xFFFFFFFF




	struct MeshEntry {
		MeshEntry()
		{
			NumIndices = 0;
			BaseVertex = 0;
			BaseIndex = 0;
			MaterialIndex = INVALID_MATERIAL;
		}

		unsigned int NumIndices;
		unsigned int BaseVertex;
		unsigned int BaseIndex;
		unsigned int MaterialIndex;
	};


	std::vector<MeshEntry> m_Entries;



	const aiScene* m_pScene;
	Assimp::Importer m_Importer;


};


#endif	

