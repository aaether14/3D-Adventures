/*


Skydome implementation


*/




#ifndef SKY_RENDER
#define SKY_REDNER





#include "texture/texture.hpp"
#include <model_loaders/aaether_loader.hpp>
#include "controls.hpp"





class SkyRender
{


	std::vector<GLuint> m_textures;
	Aa_model * model;



public:


	SkyRender();
	~SkyRender();
	void Init();
	void Clean();
	void LoadCube(const char *Directory,
		const char *PosXFilename,
		const char *NegXFilename,
		const char *PosYFilename,
		const char *NegYFilename,
		const char *PosZFilename,
		const char *NegZFilename);

	void Render(Controller * ctrl);



};

#endif