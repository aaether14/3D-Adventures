#include "ui_root.hpp"





void RootUI::Init(Controller * ctrl)
{


	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();


	Root = wmgr.loadLayoutFromFile("ui.layout");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(Root);



    
	root_settings = new RootSettings(ctrl->GetGameObject()->GetResource(), Root);
	top_root = new TopRoot(ctrl, Root);


}




void RootUI::Clean()
{


	delete root_settings;
	delete top_root;


}




void RootUI::Render(Controller * ctrl)
{


	UIManager::Render(ctrl);
	root_settings->Render(ctrl, Root);
	top_root->Render(ctrl, Root);




}