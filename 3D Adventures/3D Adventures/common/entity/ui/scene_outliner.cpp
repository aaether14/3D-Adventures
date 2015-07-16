#include "scene_outliner.hpp"




void ui_Scene::Init()
{


	CEGUI::Window *Root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
	Listbox = static_cast<CEGUI::Listbox*>(Root->getChild("Frame2/SceneOutliner"));


	Listbox->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&ui_Scene::SelectionChanged, this));


}




void ui_Scene::Clean()
{





}




void ui_Scene::AddItem(std::string name, glm::ivec2 data)
{


	CEGUI::ListboxTextItem * item = new CEGUI::ListboxTextItem(name, 0);
	item->setSelectionBrushImage("GlossySerpentFHD/TextSelectionBrush");
	Listbox->addItem(item);
	scene_data.push_back(data);


}



bool ui_Scene::SelectionChanged(const CEGUI::EventArgs& e)
{


	ClearSelectedData();
	for (CEGUI::ListboxItem * item = Listbox->getFirstSelectedItem(); item != NULL; item = Listbox->getNextSelected(item))
		selected_data.push_back(scene_data[Listbox->getItemIndex(item)]);
	return 1;


}



void ui_Scene::ClearSelectedDataFromScene()
{



	CEGUI::ListboxItem * item = Listbox->getFirstSelectedItem();

	while (item)
	{
		CEGUI::ListboxItem * temp = item;
		item = Listbox->getNextSelected(item);
		Listbox->removeItem(temp);
	}


	ClearSelectedData();


}




void ui_Scene::UpdateSceneData(GLint ind, GLint pos)
{


	for (GLuint i = 0; i < scene_data.size(); i++)
		if (scene_data[i].x == ind)
			if (scene_data[i].y == pos)
		scene_data.erase(scene_data.begin() + i);


	for (GLuint i = 0; i < scene_data.size(); i++)
		if (scene_data[i].x == ind)
			if (scene_data[i].y > pos)
				scene_data[i].y--;



	for (GLuint i = 0; i < selected_data.size(); i++)
		if (selected_data[i].x == ind)
			if (selected_data[i].y == pos)
				selected_data.erase(selected_data.begin() + i);


	for (GLuint i = 0; i < selected_data.size(); i++)
		if (selected_data[i].x == ind)
			if (selected_data[i].y > pos)
				selected_data[i].y--;

}




