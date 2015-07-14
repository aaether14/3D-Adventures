#ifndef SETTINGS_HPP
#define SETTINGS_HPP




#include "environment.hpp"
#include "filter_settings.hpp"





class Settings
{


	Environment * env;
	FilterSettings * filter_settings;



public:




	inline Settings(){ this->Init(); }
	void Init();
	


	inline ~Settings(){ this->Clean(); }
	void Clean();



	inline Environment*GetEnv(){ return this->env; }
	inline FilterSettings * GetFilterSettings(){ return this->filter_settings; }



};



#endif