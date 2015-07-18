#include "resource_loader.hpp"



void ResourceLoader::LoadResourcePaths(char *path)
{


	int i = 0;

	std::ifstream fin(path);
	std::string temp_str;

	std::string files[11];


	while (std::getline(fin,temp_str))
	{
		if (temp_str == "")continue;
		files[i] = temp_str;
		i++;
	}


	this->player_file = files[0];
	this->mount_file = files[1];
	this->weapon_file = files[2];
	this->terrain_file = files[3];
	this->color_file = files[4];
	this->static_file = files[5];
	this->env_file = files[6];
	this->fsettings_file = files[7];
	this->t_file = files[8];
	this->n_file = files[9];
	this->a_file = files[10];


	fin.close();

}



void ResourceLoader::Init()
{





}




void ResourceLoader::Clean()
{





}
