#include "settings.hpp"



void Settings::Init()
{


	this->env = new Environment();
	this->filter_settings = new FilterSettings();



}




void Settings::Clean()
{


	delete this->env;
	delete this->filter_settings;


}