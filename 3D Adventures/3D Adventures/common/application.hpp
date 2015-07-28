#ifndef APPLICATION
#define APPLICATION





#include <controls.hpp>
#include <pipeline.hpp>
#include <data_manager.hpp>
#include <ui_implementation/ui_root.hpp>
#include <base/base_module.hpp>




/**
Manager node holding the application's branches
*/
class Application : public AModule
{




public:


	/**
	Calls Init()
	*/
	inline Application() { Init(); }
	/**
	Calls Clean()
	*/
	inline ~Application() { Clean(); }


	/**
	Initializes branches
	*/
	void Init();
	/**
	Cleans branches data
	*/
	void Clean();

	/**
	Enables app
	*/
	void Enable();


};




#endif