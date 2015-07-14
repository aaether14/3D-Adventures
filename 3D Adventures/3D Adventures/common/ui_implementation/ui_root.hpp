#ifndef ROOT_UI_HPP
#define ROOT_UI_HPP




#include <ui/ui_manager.hpp>
#include "settings_root.hpp"
#include "top_root.hpp"





class RootUI : public UIManager
{



	CEGUI::Window* Root;
	RootSettings * root_settings;
	TopRoot * top_root;



public:



	inline RootUI(Controller * ctrl) : UIManager() { this->Init(ctrl); }
	void Init(Controller * ctrl);




	inline ~RootUI(){ this->Clean(); }
	void Clean();



	void Render(Controller * ctrl);



};




#endif