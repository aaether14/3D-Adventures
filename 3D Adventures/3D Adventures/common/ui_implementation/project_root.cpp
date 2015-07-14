#include "project_root.hpp"





void ui_ProjectRoot::Init(Controller * ctrl, CEGUI::Window * Root)
{



	this->ctrl = ctrl;
	this->Root = Root;




	Root->getChild("Menubar/MenuItem/PopupMenu/MenuItem")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ProjectRoot::SaveProject, this));


	Root->getChild("Menubar/MenuItem/PopupMenu/MenuItem2")->subscribeEvent(CEGUI::MenuItem::EventClicked,
		CEGUI::Event::Subscriber(&ui_ProjectRoot::LoadProject, this));




}




void ui_ProjectRoot::Clean()
{




}




void ui_ProjectRoot::SyncUI()
{




}

