/*


View tab to control which framewindows are openend


*/




#ifndef VIEW_ROOT_HPP
#define VIEW_ROOT_HPP





#include <controls.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>





class ui_ViewRoot
{



	Controller * ctrl;
	CEGUI::Window * Root;




	inline bool ViewTransform(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame3")->show();
		return 1;
	}
	


	inline bool ViewSettings(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame")->show();
		return 1;
	}



	inline bool ViewSceneOutliner(const CEGUI::EventArgs& e)
	{
		Root->getChild("Frame2")->show();
		return 1;
	}



public:



	inline ui_ViewRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	void Init(Controller * ctrl, CEGUI::Window * Root);



	inline ~ui_ViewRoot(){ this->Clean(); }
	void Clean();



	void SyncUI();



};




#endif