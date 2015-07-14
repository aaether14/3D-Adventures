#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP




#include <util/string_helper.hpp>
using namespace::AString;





class ResourceLoader
{


	std::string player_file;
	std::string mount_file;
	std::string weapon_file;

	std::string terrain_file;
	std::string color_file;
	std::string static_file;

	std::string env_file;
	std::string fsettings_file;

	std::string t_file;
	std::string n_file;
	std::string a_file;


	inline void Init(){}


public:


	ResourceLoader(){ this->Init(); }


	inline char* GetPlayerFile(){ return char_to_str(player_file); }
	inline char* GetMountFile(){ return char_to_str(mount_file); }
	inline char* GetWeaponFile(){ return char_to_str(weapon_file); }
	inline char* GetTerrainFile(){ return char_to_str(terrain_file); }
	inline char* GetColorFile(){ return char_to_str(color_file); }
	inline char* GetStaticFile(){ return char_to_str(static_file); }
	inline char* GetEnvFile(){ return char_to_str(env_file); }
	inline char* GetFSettingsFile(){ return char_to_str(fsettings_file); }
	inline char* GetTFile(){ return char_to_str(t_file); }
	inline char* GetNFile(){ return char_to_str(n_file); }
	inline char* GetAFile(){ return char_to_str(a_file); }
	void Load(char *path);


};





#endif