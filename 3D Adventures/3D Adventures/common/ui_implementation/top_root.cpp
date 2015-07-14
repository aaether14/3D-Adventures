#include "top_root.hpp"






void TopRoot::Init(Controller * ctrl, CEGUI::Window * Root)
{

	ui_project_root = new ui_ProjectRoot(ctrl, Root);


}




void TopRoot::Clean()
{



	delete ui_project_root;


}




void TopRoot::Render(Controller * ctrl, CEGUI::Window * Root)
{


	ui_project_root->SyncUI();



}
