#ifndef FILTER_ROOT_HPP
#define FILTER_ROOT_HPP




#include <settings/filter_settings.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>





class ui_FilterRoot
{



	FilterSettings * filter_settings;
	CEGUI::Window * Root;


	void Reset();


	void ResetSSAO(std::string def);
	void ResetHDR(std::string def);
	void ResetFXAA(std::string def);
	void ResetDoF(std::string def);
	void SyncSSAO(std::string def);
	void SyncHDR(std::string def);
	void SyncFXAA(std::string def);
	void SyncDoF(std::string def);


public:



	inline ui_FilterRoot(FilterSettings * filter_settings, CEGUI::Window * Root){ this->Init(filter_settings, Root); }
	void Init(FilterSettings * filter_settings, CEGUI::Window * Root);


	
	inline ~ui_FilterRoot(){ this->Clean(); }
	void Clean();



	void SyncUI();



};



#endif