#ifndef PROJECT_ROOT_HPP
#define PROJECT_ROOT_HPP





#include <controls.hpp>
#include <data_manager.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>






/**


Provinding callbacks for Save/Load on ui layout


*/
class ui_ProjectRoot
{



	Controller * ctrl;
	CEGUI::Window * Root;



	/**
	Callback for handling project saving
	*/
	inline bool SaveProject(const CEGUI::EventArgs &args)
	{
		static_cast<DataManager*>(ctrl->Get("DataManager"))->GetResource()->SaveChanges();
		return 1;
	}


	/**
	Callback for handling project loading
	*/
	inline bool LoadProject(const CEGUI::EventArgs &args)
	{
		static_cast<DataManager*>(ctrl->Get("DataManager"))->GetResource()->LoadChanges();
		return 1;
	}




public:



	/**
	Calls Init()
	*/
	inline ui_ProjectRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	/**
	Initializes out of UI layout
	*/
	void Init(Controller * ctrl, CEGUI::Window * Root);



	/**
	Calls Clean()
	*/
	inline ~ui_ProjectRoot(){ this->Clean(); }
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