#include "assimp_converter.hpp"








bool AssimpConverter::ConvertModel(const std::string& Filename)
{


	bool Ret = false;

	m_pScene = m_Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (m_pScene)
		Ret = InitFromScene(m_pScene, Filename);
	else 
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), m_Importer.GetErrorString());


	return Ret;
}


bool AssimpConverter::InitFromScene(const aiScene* pScene, const std::string& Filename)
{


	m_Entries.resize(pScene->mNumMeshes);




	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> TexCoords;
	std::vector<GLuint> Indices;



	GLuint NumVertices = 0;
	GLuint NumIndices = 0;



	// Count the number of vertices and indices
	for (GLuint i = 0; i < m_Entries.size(); i++) 
	{


		m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_Entries[i].BaseVertex = NumVertices;
		m_Entries[i].BaseIndex = NumIndices;

		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += m_Entries[i].NumIndices;


	}

	// Reserve space in the vectors for the vertex attributes and indices
	Positions.reserve(NumVertices);
	Normals.reserve(NumVertices);
	TexCoords.reserve(NumVertices);
	Indices.reserve(NumIndices);



	// Initialize the meshes in the scene one by one
	for (GLuint i = 0; i < m_Entries.size(); i++)
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		InitMesh(i, paiMesh, Positions, Normals, TexCoords, Indices);
	}




	std::string path = Filename.substr(0, Filename.find_last_of("\\") + 1);



	GLint size1;
	std::ofstream os(AString::char_to_str(std::string(path + "model.aao")), std::ios::binary);
	size1 = Positions.size();
	os.write((const char*)&size1, sizeof(GLint));
	os.write((const char*)&Positions[0], size1 * sizeof(glm::vec3));
	size1 = Normals.size();
	os.write((const char*)&size1, sizeof(GLint));
	os.write((const char*)&Normals[0], size1 * sizeof(glm::vec3));
	size1 = TexCoords.size();
	os.write((const char*)&size1, sizeof(GLint));
	os.write((const char*)&TexCoords[0], size1 * sizeof(glm::vec2));
	size1 = Indices.size();
	os.write((const char*)&size1, sizeof(GLint));
	os.write((const char*)&Indices[0], size1 * sizeof(GLuint));
	size1 = m_Entries.size();
	os.write((const char*)&size1, sizeof(GLint));
	os.write((const char*)&m_Entries[0], size1 * sizeof(MeshEntry));
	size1 = pScene->mNumMaterials;
	os.write((const char*)&size1, sizeof(GLuint));
	os.close();

	os.open(AString::char_to_str(std::string(path + "model.aam")));
	for (int i = 0; i < pScene->mNumMaterials; i++)
	{
		os << i << std::endl;
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				std::string p(Path.data);
				p = p.substr(p.find_last_of("/") + 1, p.length());
				os << "1" << " " << p << std::endl;
			}
		}
		else
		{
			aiColor3D color(0.f, 0.f, 0.f);
			pMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			os << "2" << " " << color.r << " " << color.g << " " << color.b << std::endl;
		}
	}
	os.close();




	

	return true;
}


void AssimpConverter::InitMesh(GLuint MeshIndex,
	const aiMesh* paiMesh,
	std::vector<glm::vec3>& Positions,
	std::vector<glm::vec3>& Normals,
	std::vector<glm::vec2>& TexCoords,
	std::vector<GLuint>& Indices)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);



	// Populate the vertex attribute vectors
	for (GLuint i = 0; i < paiMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(paiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(paiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

		Positions.push_back(glm::vec3(pPos->x, pPos->y, pPos->z));
		Normals.push_back(glm::vec3(pNormal->x, pNormal->y, pNormal->z));
		TexCoords.push_back(glm::vec2(pTexCoord->x, pTexCoord->y));
	}


	// Populate the index buffer
	for (GLuint i = 0; i < paiMesh->mNumFaces; i++) 
	{


		const aiFace& Face = paiMesh->mFaces[i];
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);


	}
}






