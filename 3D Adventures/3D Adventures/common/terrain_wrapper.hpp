#ifndef TERRAIN_WRAPPER
#define TERRAIN_WRAPPER




#include <light/light.hpp>
#include <terrain/terrain.hpp>
#include "controls.hpp"




class TerrainWrapper : public TerrainShader
{



	Light *TerrainLight;
	Terrain*PipeTerrain;



	void ManagePlayerCollision(Controller*ctrl, bool null_gravity);



public:



	inline ~TerrainWrapper(){ this->Clean(); }



	void Init();
	void Clean();


	inline  Light*getLight() { return this->TerrainLight; }


	void Enable();
	void Render();






};


#endif