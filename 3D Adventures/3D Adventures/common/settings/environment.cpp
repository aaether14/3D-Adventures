#include "environment.hpp"




void Environment::Reset()
{


	this->sun_dir = glm::vec3(
		sin(M_PI / 180 * 25),
		-cos(M_PI / 180 * 25),
		0.0f
		);


	this->sun_color = glm::vec3(1.0f, 1.0f, 1.0f);


	this->model_ambient = 0.5f;
	this->terrain_ambient = 0.5f;
	this->model_diffuse = 1.0f;
	this->terrain_diffuse = 1.5f;


	this->terrain_bright = 1.0f;
	this->model_bright = 1.3f;




	this->fog_color = glm::vec3(0.964f, 0.913f, 0.705f);
	this->fog_density = 0.00175f;



	this->should_reset = false;


}



void Environment::Save(char *path)
{


	std::ofstream fout(path, std::ios::binary);
	AFile::WriteToFile(fout, sun_dir);
	AFile::WriteToFile(fout, sun_color);
	AFile::WriteToFile(fout, model_ambient);
	AFile::WriteToFile(fout, terrain_ambient);
	AFile::WriteToFile(fout, model_diffuse);
	AFile::WriteToFile(fout, terrain_diffuse);
	AFile::WriteToFile(fout, model_bright);
	AFile::WriteToFile(fout, terrain_bright);
	AFile::WriteToFile(fout, fog_color);
	AFile::WriteToFile(fout, fog_density);
	fout.close();



}



void Environment::Load(char*path)
{



	std::ifstream fin(path, std::ios::binary);
	AFile::ReadFromFile(fin, sun_dir);
	AFile::ReadFromFile(fin, sun_color);
	AFile::ReadFromFile(fin, model_ambient);
	AFile::ReadFromFile(fin, terrain_ambient);
	AFile::ReadFromFile(fin, model_diffuse);
	AFile::ReadFromFile(fin, terrain_diffuse);
	AFile::ReadFromFile(fin, model_bright);
	AFile::ReadFromFile(fin, terrain_bright);
	AFile::ReadFromFile(fin, fog_color);
	AFile::ReadFromFile(fin, fog_density);
	fin.close();


}






void Environment::Init()
{


	this->Reset();


}