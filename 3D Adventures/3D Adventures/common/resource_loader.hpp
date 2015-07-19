#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP




#include <base/base_resource_loader.hpp>





class ResourceLoader : public BaseResourceLoader
{



	std::string terrain_file;
	std::string color_file;
	std::string t_file;
	std::string n_file;
	std::string a_file;


	std::string env_file;
	std::string fsettings_file;



public:


	ResourceLoader(){ Init(); }
	void Init();


	~ResourceLoader(){ Clean(); }
	void Clean();



	inline char* GetTerrainFile(){ return char_to_str(terrain_file); }
	inline char* GetColorFile(){ return char_to_str(color_file); }
	inline char* GetEnvFile(){ return char_to_str(env_file); }
	inline char* GetFSettingsFile(){ return char_to_str(fsettings_file); }
	inline char* GetTFile(){ return char_to_str(t_file); }
	inline char* GetNFile(){ return char_to_str(n_file); }
	inline char* GetAFile(){ return char_to_str(a_file); }


	void LoadResourcePaths(char *path);


};





#endif