#ifndef MESH_WRAPPER
#define MESH_WRAPPER



#include "mesh_drawer.hpp"





class MeshWrapper : public MeshShader
{

	
	MeshDrawer * Drawer;




public:




	inline MeshWrapper(Controller *ctrl){ this->Init(ctrl); }
	inline ~MeshWrapper(){ this->Clean(); }


	void Init(Controller * ctrl);
	void Clean();




	void FirstPass(Controller *ctrl);
	void Enable(Controller * ctrl);
	void Render(Controller * ctrl);




};


#endif