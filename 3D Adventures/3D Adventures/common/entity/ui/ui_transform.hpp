#ifndef TRANSFORM_UI_HPP
#define TRANSFORM_UI_HPP




#include <controls.hpp>
#include <CEGUI/CEGUI.h>




class ui_Transform
{


	CEGUI::Window * FrameRoot;


	bool RadioPositionChanged(const CEGUI::EventArgs& e);
	bool RadioRotationChanged(const CEGUI::EventArgs& e);
	bool RadioScaleChanged(const CEGUI::EventArgs& e);


	bool SpinnerPositionChanged(const CEGUI::EventArgs& e);
	bool SpinnerRotationChanged(const CEGUI::EventArgs& e);
	bool SpinnerScaleChanged(const CEGUI::EventArgs& e);


	inline bool CloseWindow(const CEGUI::EventArgs& e){ FrameRoot->hide(); return 1; }




	class PaletteInfo
	{


	public:


		glm::mat3 trans;
		inline void Reset(){ trans[0] = glm::vec3(0.0); trans[1] = glm::vec3(0.0); trans[2] = glm::vec3(1.0); }


	}*p_info;


	GLuint update_id;



public:



	inline ui_Transform(){ this->Init(); }
	void Init();




	inline ~ui_Transform(){ this->Clean(); }
	void Clean();


	inline PaletteInfo * GetPInfo(){ return p_info; }


	void UpdateData();
	void UpdateStepData(GLfloat step_size);


};



#endif