/*


Storing settings on ui side


*/



#ifndef SETTINGS_ROOT_HPP
#define SETTINGS_ROOT_HPP




#include "controls.hpp"
#include <CEGUI/CEGUI.h>
#include "lighting_root.hpp"
#include "filter_root.hpp"
#include "../settings/settings.hpp"





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


	inline bool CloseWindow(const CEGUI::EventArgs& e)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Frame")->hide();
		return 1;
	}
	




	ui_LightingRoot * ui_lighting_root;
	ui_FilterRoot * ui_filter_root;





public:



	inline RootSettings(ResourceLoader * res, CEGUI::Window * Root){ this->Init(res, Root); }
	void Init(ResourceLoader * res, CEGUI::Window * Root);



	inline ~RootSettings(){ this->Clean(); }
	void Clean();



	void Render(Controller * ctrl, CEGUI::Window * Root);




};




#endif