#ifndef SKY_RENDER
#define SKY_REDNER





#include "texture/texture.hpp"
#include <model_loaders/aaether_loader.hpp>
#include "controls.hpp"




/**


Skydome implementation


*/
class SkyRender
{


	std::vector<GLuint> m_textures;
	Aa_model * model;



public:


	/**
	Calls Init()
	*/
	SkyRender();
	/**
	Calls Clean()
	*/
	~SkyRender();
	/**
	Inits model
	*/
	void Init();
	/**
	Cleans model and textures
	*/
	void Clean();
	/**
	Loads a cube map and stores it
	*/
	void LoadCube(const char *Directory,
		const char *PosXFilename,
		const char *NegXFilename,
		const char *PosYFilename,
		const char *NegYFilename,
		const char *PosZFilename,
		const char *NegZFilename);

	/**
	Renders to scene
	*/
	void Render(Controller * ctrl);



};

#endif