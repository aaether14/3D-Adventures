#ifndef LIGHT_ROOT_HPP
#define LIGHT_ROOT_HPP




#include <settings/environment.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>




/**


Lighting settings ui layout management


*/
class ui_LightingRoot
{



	Environment * env;
	CEGUI::Window * Root;


	/**
	Reset state
	*/
	void Reset();



public:



	/**
	Calls Init()
	*/
	inline ui_LightingRoot(Environment * env, CEGUI::Window * Root){ this->Init(env, Root); }
	/**
	Initializes UI from layout
	*/
	void Init(Environment * env, CEGUI::Window * Root);



	/**
	Calls Clean()
	*/
	inline ~ui_LightingRoot(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Sync UI with internal data when requested
	*/
	void SyncUI();




};




#endif