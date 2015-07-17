#ifndef PROJECT_ROOT_HPP
#define PROJECT_ROOT_HPP





#include <controls.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>





class ui_ProjectRoot
{



	Controller * ctrl;
	CEGUI::Window * Root;




	inline bool SaveProject(const CEGUI::EventArgs &args)
	{
		ctrl->GetGameObject()->GetResource()->SaveChanges();
		return 1;
	}



	inline bool LoadProject(const CEGUI::EventArgs &args)
	{
		ctrl->GetGameObject()->GetResource()->LoadChanges();
		return 1;
	}




public:



	inline ui_ProjectRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	void Init(Controller * ctrl, CEGUI::Window * Root);



	inline ~ui_ProjectRoot(){ this->Clean(); }
	void Clean();



	void SyncUI();



};




#endif