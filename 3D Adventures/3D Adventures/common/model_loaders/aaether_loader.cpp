#include "aaether_loader.hpp"




#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2





Aa_model::Aa_model()
{


	m_VAO = 0;
	ZERO_MEM(m_Buffers);


}




Aa_model::~Aa_model()
{



	for (uint i = 0; i < m_Textures.size(); i++) {
		glDeleteTextures(1, &this->m_Textures[i]);
	}



	if (m_Buffers[0] != 0) {
		glDeleteBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);
	}




	if (m_VAO != 0) {
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}




}




void Aa_model::Load(const char* path)
{



	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(this->m_VAO);
	glGenBuffers(ARRAY_SIZE_IN_ELEMENTS(m_Buffers), m_Buffers);



	size_t size1, size2;
	std::vector<Vector3f> Positions;
	std::vector<Vector3f> Normals;
	std::vector<Vector2f> TexCoords;
	std::vector<GLuint> Indices;
	GLuint mnumMaterials;
	GLdouble time = glfwGetTime();



	ifstream is(path, ios::binary);
	is.read((char*)&size2, sizeof(GLint));
	Positions.resize(size2);
	is.read((char*)&Positions[0], size2 * sizeof(Vector3f));
	is.read((char*)&size2, sizeof(GLint));
	Normals.resize(size2);
	is.read((char*)&Normals[0], size2 * sizeof(Vector3f));
	is.read((char*)&size2, sizeof(GLint));
	TexCoords.resize(size2);
	is.read((char*)&TexCoords[0], size2 * sizeof(Vector2f));
	is.read((char*)&size2, sizeof(GLint));
	Indices.resize(size2);
	is.read((char*)&Indices[0], size2 * sizeof(GLuint));
	is.read((char*)&size2, sizeof(GLint));
	m_Entries.resize(size2);
	is.read((char*)&m_Entries[0], size2 * sizeof(Aa_entry));
	is.read((char*)&mnumMaterials, sizeof(GLuint));
	m_Textures.resize(mnumMaterials);
	is.close();
	std::string tex_path(path);
	tex_path = tex_path.substr(0, tex_path.length()-4) + ".aam";
	is.open(tex_path.c_str());
	tex_path = tex_path.substr(0,tex_path.find_last_of("/")+1);
	for (int i = 0; i < mnumMaterials; i++)
	{

		GLuint ind, type;
		Vector3f color;
		std::string mat_path;

		is >> ind >> type;
		if (type == 1){
			is >> mat_path;
			mat_path = tex_path + mat_path;
			this->m_Textures[ind] = TextureObject::load_texture(AString::char_to_str(mat_path), GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		}
		else if (type == 2){
			is >> color.x >> color.y >> color.z;
			this->m_Textures[ind] = TextureObject::create_texture_from_color(color.x, color.y, color.z);
		}
	}
	is.close();



	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Positions[0]) * Positions.size(), &Positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexCoords[0]) * TexCoords.size(), &TexCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals[0]) * Normals.size(), &Normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);



}

void Aa_model::Render()
{
	glBindVertexArray(m_VAO);

	for (GLint i = 0; i < m_Entries.size(); i++) 
	{
		const GLuint MaterialIndex = m_Entries[i].MaterialIndex;
		assert(MaterialIndex < m_Textures.size());


		if (m_Textures[MaterialIndex]) 
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->m_Textures[MaterialIndex]);
		}


		glDrawElementsBaseVertex(GL_TRIANGLES,
			m_Entries[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(GLint)* m_Entries[i].BaseIndex),
			m_Entries[i].BaseVertex);


	}


	glBindVertexArray(0);
}