#ifndef SCENE_OUTLINER_HPP
#define SCENE_OUTLINER_HPP




#include <controls.hpp>
#include <CEGUI/CEGUI.h>




class ui_Scene
{


	CEGUI::Listbox * Listbox;
	std::vector<glm::ivec2>scene_data;
	std::vector<glm::ivec2>selected_data;


	bool SelectionChanged(const CEGUI::EventArgs& e);



	inline bool CloseWindow(const CEGUI::EventArgs& e)
	{
		CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->getChild("Frame2")->hide();
		return 1;
	}



public:



	inline ui_Scene(){ this->Init(); }
	void Init();




	inline ~ui_Scene(){ this->Clean(); }
	void Clean();



	void AddItem(std::string name, glm::ivec2 data);
	inline std::vector<glm::ivec2>GetSelectedData(){ return selected_data; }


	inline void ClearSelectedData(){ selected_data.clear(); }


	void ClearSelectedDataFromScene();
	void UpdateSceneData(GLint ind, GLint pos);


};



#endif