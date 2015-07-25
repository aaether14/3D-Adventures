#ifndef APPLICATION
#define APPLICATION



#include "controls.hpp"
#include "pipeline.hpp"
#include <ui_implementation/ui_root.hpp>
#include <base/base_module.hpp>




class Application : public AModule
{



	Pipeline * pipe;
	RootUI * root_ui;



public:

	inline Application() { this->Init(); }
	inline ~Application() { this->Terminate(); }


	int Init();
	void Terminate();


	void SetFlags();
	void Load(char*path);


	void Render();


};




#endif