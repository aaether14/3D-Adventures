#ifndef SCENE_OUTLINER_HPP
#define SCENE_OUTLINER_HPP




#include <controls.hpp>
#include <CEGUI/CEGUI.h>



/**


Scene outliner
WIP


*/
class ui_SceneOutliner
{


	CEGUI::Listbox * Listbox;
	std::vector<glm::ivec2>scene_data;
	std::vector<glm::ivec2>selected_data;


	/**
	Callback triggered EventSelectionChanged event
	*/
	bool SelectionChanged(const CEGUI::EventArgs& e);


	/**
	Callback to process clicking 'X'
	*/
	inline bool CloseWindow(const CEGUI::EventArgs& e)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Frame2")->hide();
		return 1;
	}



public:


	/**
	Calls Init()
	*/
	inline ui_SceneOutliner(){ this->Init(); }
	/**
	Initialize data
	*/
	void Init();



	/**
	Calls Clean()
	*/
	inline ~ui_SceneOutliner(){ this->Clean(); }
	/**
	Cleans data
	*/
	void Clean();


	/**
	Add item to scene outliner (UI wise)
	*/
	void AddItem(std::string name, glm::ivec2 data);
	/**
	Get data selected in the scene outliner
	*/
	inline std::vector<glm::ivec2>GetSelectedData(){ return selected_data; }

	/**
	Clear data selected from scene outliner
	*/
	inline void ClearSelectedData(){ selected_data.clear(); }


	/**
	Delete selected data (UI wise)
	*/
	void ClearSelectedDataFromScene();
	/**
	Update scene outliner data due to deletion
	*/
	void UpdateSceneData(GLint ind, GLint pos);


};



#endif