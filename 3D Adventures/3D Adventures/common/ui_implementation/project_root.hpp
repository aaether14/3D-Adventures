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
		ctrl->GetGameObject()->GetSettings()->GetEnv()->Save(ctrl->GetGameObject()->GetResource()->GetEnvFile());
		ctrl->GetGameObject()->GetSettings()->GetFilterSettings()->Save(ctrl->GetGameObject()->GetResource()->GetFSettingsFile());
		return 1;
	}



	inline bool LoadProject(const CEGUI::EventArgs &args)
	{
		ctrl->GetGameObject()->GetSettings()->GetEnv()->Load(ctrl->GetGameObject()->GetResource()->GetEnvFile());
		ctrl->GetGameObject()->GetSettings()->GetFilterSettings()->Load(ctrl->GetGameObject()->GetResource()->GetFSettingsFile());
		ctrl->GetGameObject()->GetSettings()->GetEnv()->should_reset = true;
		ctrl->GetGameObject()->GetSettings()->GetFilterSettings()->should_reset = true;
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