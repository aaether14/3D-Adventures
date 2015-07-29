#include "ui_root.hpp"





void RootUI::Init()
{


	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	Root = wmgr.loadLayoutFromFile("ui.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(Root);


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	DataManager * dm = static_cast<DataManager*>(GetManager()->Get("DataManager"));


	root_settings = new RootSettings(dm->GetResource(), Root);
	top_root = new TopRoot(dm, Root);




}




void RootUI::Clean()
{


	delete root_settings;
	delete top_root;


}




void RootUI::Enable()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));


	UIManager::Enable();
	root_settings->Render(ctrl, Root);
	top_root->Render(ctrl, Root);




}