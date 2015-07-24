#ifndef VIEW_ROOT_HPP
#define VIEW_ROOT_HPP





#include <controls.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>






/**


View tab to control which framewindows are openend


*/
class ui_ViewRoot
{



	Controller * ctrl;
	CEGUI::Window * Root;




	/**
	Handles openening of the transform tab
	*/
	inline bool ViewTransform(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame3")->show();
		return 1;
	}
	


	/**
	Handles openening of the settings tab
	*/
	inline bool ViewSettings(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame")->show();
		return 1;
	}



	/**
	Handles openening of the scene outliner tab
	*/
	inline bool ViewSceneOutliner(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame2")->show();
		return 1;
	}



public:



	/**
	Calls Init()
	*/
	inline ui_ViewRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	/**
	Initializes data and sets callbacks
	*/
	void Init(Controller * ctrl, CEGUI::Window * Root);


	/**
	Calls Clean()
	*/
	inline ~ui_ViewRoot(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Sync UI side to internal data side
	*/
	void SyncUI();



};




#endif