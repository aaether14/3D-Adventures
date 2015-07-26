#ifndef APPLICATION
#define APPLICATION



#include "controls.hpp"
#include "pipeline.hpp"
#include <ui_implementation/ui_root.hpp>
#include <base/base_module.hpp>




class Application : public AModule
{




public:


	inline Application() { Init(); }
	inline ~Application() { Clean(); }


	void Init();
	void Clean();


	void Enable();


};




#endif