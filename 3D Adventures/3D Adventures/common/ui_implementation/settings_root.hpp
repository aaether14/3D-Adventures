#ifndef SETTINGS_ROOT_HPP
#define SETTINGS_ROOT_HPP




#include "controls.hpp"
#include <CEGUI/CEGUI.h>
#include "lighting_root.hpp"
#include "filter_root.hpp"





class RootSettings
{


	GLboolean is_inside_window;



	inline bool MouseInside(const CEGUI::EventArgs& args)
	{
		is_inside_window = true;
		return true;
	}
	inline bool MouseOutside(const CEGUI::EventArgs& args)
	{
		is_inside_window = false;
		return true;
	}
	




	ui_LightingRoot * ui_lighting_root;
	ui_FilterRoot * ui_filter_root;





public:



	inline RootSettings(Settings * settings, CEGUI::Window * Root){ this->Init(settings, Root); }
	void Init(Settings * setting, CEGUI::Window * Root);



	inline ~RootSettings(){ this->Clean(); }
	void Clean();



	void Render(Controller * ctrl, CEGUI::Window * Root);




};




#endif