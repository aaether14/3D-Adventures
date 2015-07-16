#include "ui_transform.hpp"




void ui_Transform::Init()
{


	CEGUI::Window *Root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	FrameRoot = Root->getChild("Frame3");




	static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
		CEGUI::Event::Subscriber(&ui_Transform::RadioPositionChanged, this));
	static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton2"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
		CEGUI::Event::Subscriber(&ui_Transform::RadioRotationChanged, this));
	static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton3"))->subscribeEvent(CEGUI::RadioButton::EventSelectStateChanged,
		CEGUI::Event::Subscriber(&ui_Transform::RadioScaleChanged, this));



	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
		CEGUI::Event::Subscriber(&ui_Transform::SpinnerPositionChanged, this));
	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
		CEGUI::Event::Subscriber(&ui_Transform::SpinnerRotationChanged, this));
	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->subscribeEvent(CEGUI::Spinner::EventValueChanged,
		CEGUI::Event::Subscriber(&ui_Transform::SpinnerScaleChanged, this));




	p_info = new PaletteInfo();
	p_info->file_name = "data/terrain_files/test.st";
	p_info->Reset();


	update_id = 0;
	static_cast<CEGUI::RadioButton*>(FrameRoot->getChild("RadioButton"))->setSelected(true);


}




void ui_Transform::Clean()
{





}




void ui_Transform::UpdateData()
{

	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->setCurrentValue(p_info->trans[update_id].x);
	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->setCurrentValue(p_info->trans[update_id].y);
	static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->setCurrentValue(p_info->trans[update_id].z);

}




bool ui_Transform::RadioPositionChanged(const CEGUI::EventArgs& e)
{

	update_id = 0;
	UpdateData();
	return 1;

}



bool ui_Transform::RadioRotationChanged(const CEGUI::EventArgs& e)
{

	update_id = 1;
	UpdateData();
	return 1;

}



bool ui_Transform::RadioScaleChanged(const CEGUI::EventArgs& e)
{

	update_id = 2;
	UpdateData();
	return 1;

}




bool ui_Transform::SpinnerPositionChanged(const CEGUI::EventArgs& e)
{

	p_info->trans[update_id].x = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner"))->getCurrentValue();
	return 1;
}



bool ui_Transform::SpinnerRotationChanged(const CEGUI::EventArgs& e)
{
	
	p_info->trans[update_id].y = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner2"))->getCurrentValue();
	return 1;
}



bool ui_Transform::SpinnerScaleChanged(const CEGUI::EventArgs& e)
{

	p_info->trans[update_id].z = static_cast<CEGUI::Spinner*>(FrameRoot->getChild("Spinner3"))->getCurrentValue();
	return 1;
}


