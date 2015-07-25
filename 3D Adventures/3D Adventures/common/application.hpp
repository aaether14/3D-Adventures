#ifndef APPLICATION
#define APPLICATION



#include "controls.hpp"
#include "pipeline.hpp"
#include <ui_implementation/ui_root.hpp>
#include <base/base_module.hpp>




class Application : public AModule
{




public:

	inline Application() { this->Init(); }
	inline ~Application() { this->Clean(); }


	void Init();
	void Clean();


	void Load(char*path);
	void Enable();


};




#endif