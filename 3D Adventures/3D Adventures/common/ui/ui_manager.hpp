/*


CEGUI initialisation


*/




#ifndef UI_MANAGER
#define UI_MANAGER




#include <controller/controls_source.hpp>
#include <texture/texture.hpp>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <CEGUI/CommonDialogs/ColourPicker/ColourPicker.h>
#include <CEGUI/CEGUI.h>





class UIManager
{




public:



	inline UIManager(){ this->Init(); }
	void Init();



	inline ~UIManager(){ this->Clean(); }
	void Clean();



	void Render(ControllerSource * ctrl);




};






#endif