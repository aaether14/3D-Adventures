#include "settings_root.hpp"




void RootSettings::Init(Settings * settings, CEGUI::Window * Root)
{


	is_inside_window = false;
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();



	Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("lighting.layout"));
	Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("ssao.layout"));
	Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("hdr.layout"));
	Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("fxaa.layout"));
	Root->getChild("Frame/Settings")->addChild(wmgr.loadLayoutFromFile("dof.layout"));



	Root->getChild("Frame")->subscribeEvent(CEGUI::Window::EventMouseLeavesArea, 
		CEGUI::Event::Subscriber(&RootSettings::MouseOutside, this));

	Root->getChild("Frame")->subscribeEvent(CEGUI::Window::EventMouseEntersArea,
		CEGUI::Event::Subscriber(&RootSettings::MouseInside, this));



	ui_lighting_root = new ui_LightingRoot(settings->GetEnv(), Root);
	ui_filter_root = new ui_FilterRoot(settings->GetFilterSettings(), Root);




}




void RootSettings::Clean()
{

	
	delete ui_lighting_root;
	delete ui_filter_root;


}




void RootSettings::Render(Controller * ctrl, CEGUI::Window * Root)
{


	if (!is_inside_window && ctrl->GetMouseButton(GLFW_MOUSE_BUTTON_LEFT))
		Root->getChild("Frame")->deactivate();




	ui_lighting_root->SyncUI();
	ui_filter_root->SyncUI();


}

