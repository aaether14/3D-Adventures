#ifndef UI_MANAGER
#define UI_MANAGER




#include <controller/controls_source.hpp>
#include <texture/texture.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <CEGUI/CEGUI.h>




/**


CEGUI initialisation


*/
class UIManager
{




public:



	/**
	Calls Init()
	*/
	inline UIManager(){ this->Init(); }
	/**
	Initializes CEGUI
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~UIManager(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();



	/**
	Renders UI to scene 
	*/
	void Render(ControllerSource * ctrl);




};






#endif