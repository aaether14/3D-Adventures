#ifndef TOP_ROOT_HPP
#define TOP_ROOT_HPP





#include <controls.hpp>
#include <CEGUI/CEGUI.h>
#include "project_root.hpp"
#include "view_root.hpp"






/**


Top bar ui layout management


*/
class TopRoot
{


	ui_ProjectRoot * ui_project_root;
	ui_ViewRoot * ui_view_root;


public:



	/**
	Calls Init()
	*/
	inline TopRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	/**
	Initializes top bar layout
	*/
	void Init(Controller * ctrl, CEGUI::Window * Root);


	/**
	Calls Clean()
	*/
	inline ~TopRoot(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Renders top bar ui layout to screen
	*/
	void Render(Controller * ctrl, CEGUI::Window * Root);



};



#endif