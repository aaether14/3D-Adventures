#ifndef MESH_WRAPPER
#define MESH_WRAPPER




#include <light/light.hpp>
#include "mesh_drawer.hpp"





class MeshWrapper : public MeshShader
{

	
	Light *MeshLight;
	MeshDrawer * Drawer;




public:



	inline ~MeshWrapper(){ this->Clean(); }


	void Init();
	void Clean();



	inline Light*getLight(){ return this->MeshLight; }



	void Enable();
	void Render();




};


#endif