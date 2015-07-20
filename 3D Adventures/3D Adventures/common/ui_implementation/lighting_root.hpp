/*


Lighting settings ui layout management


*/



#ifndef LIGHT_ROOT_HPP
#define LIGHT_ROOT_HPP




#include <settings/environment.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>





class ui_LightingRoot
{



	Environment * env;
	CEGUI::Window * Root;



	void Reset();



public:



	inline ui_LightingRoot(Environment * env, CEGUI::Window * Root){ this->Init(env, Root); }
	void Init(Environment * env, CEGUI::Window * Root);



	inline ~ui_LightingRoot(){ this->Clean(); }
	void Clean();




	void SyncUI();




};




#endif