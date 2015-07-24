#ifndef ROOT_UI_HPP
#define ROOT_UI_HPP




#include <ui/ui_manager.hpp>
#include "settings_root.hpp"
#include "top_root.hpp"






/**


Accesing UI through UIManager and getting pointer of window root


*/
class RootUI : public UIManager
{



	CEGUI::Window* Root;
	RootSettings * root_settings;
	TopRoot * top_root;



public:



	/**
	Calls Init()
	*/
	inline RootUI(Controller * ctrl) : UIManager() { this->Init(ctrl); }
	/**
	Initializes UI layouts
	*/
	void Init(Controller * ctrl);





	/**
	Calls Clean()
	*/
	inline ~RootUI(){ this->Clean(); }
	/**
	Cleans UI layouts data
	*/
	void Clean();



	/**
	Renders all layouts to screen
	*/
	void Render(Controller * ctrl);



};




#endif