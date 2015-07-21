#include "resource_loader.hpp"



void ResourceLoader::LoadResourcePaths(char *path)
{


	int i = 0;

	std::ifstream fin(path);
	std::string temp_str;

	std::string files[8];


	while (std::getline(fin,temp_str))
	{
		if (temp_str == "")continue;
		files[i] = temp_str;
		i++;
	}


	terrain_file = files[0];
	color_file = files[1];
	t_file = files[2];
	n_file = files[3];
	a_file = files[4];


	env_file = files[5];
    fsettings_file = files[6];
	scene_file = files[7];


	fin.close();

}



void ResourceLoader::Init()
{





}




void ResourceLoader::Clean()
{





}
