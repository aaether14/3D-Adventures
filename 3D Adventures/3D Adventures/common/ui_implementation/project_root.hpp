#ifndef PROJECT_ROOT_HPP
#define PROJECT_ROOT_HPP





#include <data_manager.hpp>
#include <CEGUI/CEGUI.h>
#include <util/string_helper.hpp>
#include <ui/ui_util.hpp>






/**


Provinding callbacks for Save/Load on ui layout


*/
class ui_ProjectRoot
{



	DataManager * dm;
	CEGUI::Window * Root;



	/**
	Callback for handling project saving
	*/
	inline bool SaveProject(const CEGUI::EventArgs &args)
	{
		dm->GetResource()->SaveChanges();
		return 1;
	}


	/**
	Callback for handling project loading
	*/
	inline bool LoadProject(const CEGUI::EventArgs &args)
	{
		dm->GetResource()->LoadChanges();
		return 1;
	}


	/**
	Callback for handling project reseting
	*/
	inline bool ResetProject(const CEGUI::EventArgs &args)
	{
		dm->GetResource()->NoChanges();
		return 1;
	}




public:



	/**
	Calls Init()
	*/
	inline ui_ProjectRoot(DataManager * dm, CEGUI::Window * Root){ this->Init(dm, Root); }
	/**
	Initializes out of UI layout
	*/
	void Init(DataManager * dm, CEGUI::Window * Root);



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