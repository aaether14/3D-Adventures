#ifndef TERRAIN_WRAPPER
#define TERRAIN_WRAPPER




#include <light/light.hpp>
#include <terrain/terrain.hpp>
#include "controls.hpp"




class TerrainWrapper : public TerrainShader
{



	Light *TerrainLight;
	Terrain*PipeTerrain;



public:



	inline TerrainWrapper(Controller * ctrl){ this->Init(ctrl); }
	inline ~TerrainWrapper(){ this->Clean(); }



	void Init(Controller * ctrl);
	void Clean();


	inline  Light*getLight() { return this->TerrainLight; }


	void Enable(Controller*ctrl);
	void FirstPass(Controller *ctrl);
	void Render(Controller * ctrl);



	void ManagePlayerCollision(Controller*ctrl, bool null_gravity);


};


#endif