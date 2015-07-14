#ifndef MESH_WRAPPER
#define MESH_WRAPPER




#include <light/light.hpp>
#include "mesh_drawer.hpp"





class MeshWrapper
{

	

	MeshShader * mesh_shader;
	Light *MeshLight;
	MeshDrawer * Drawer;




public:




	inline MeshWrapper(Controller *ctrl){ this->Init(ctrl); }
	inline ~MeshWrapper(){ this->Clean(); }


	void Init(Controller * ctrl);
	void Clean();



	inline Light*getLight(){ return this->MeshLight; }



	void FirstPass(Controller *ctrl);
	void Enable(Controller * ctrl);
	void Render(Controller * ctrl);




};


#endif