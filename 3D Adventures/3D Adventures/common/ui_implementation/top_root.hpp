#ifndef TOP_ROOT_HPP
#define TOP_ROOT_HPP





#include "controls.hpp"
#include <CEGUI/CEGUI.h>
#include "project_root.hpp"





class TopRoot
{


	ui_ProjectRoot * ui_project_root;


public:



	inline TopRoot(Controller * ctrl, CEGUI::Window * Root){ this->Init(ctrl, Root); }
	void Init(Controller * ctrl, CEGUI::Window * Root);


	inline ~TopRoot(){ this->Clean(); }
	void Clean();



	void Render(Controller * ctrl, CEGUI::Window * Root);



};



#endif