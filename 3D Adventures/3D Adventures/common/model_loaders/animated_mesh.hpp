#ifndef ANIMATED_MESH
#define ANIMATED_MESH



#include <model_loaders/assimp_loader.hpp>




#define MAX_BONES 100





class AnimatedMesh
{



	vector<Matrix4f> transform;
	Mesh * mesh;
	double m_startTime;




public:



	inline AnimatedMesh(char*path) { this->Init(path); };
	inline ~AnimatedMesh();
	void Init(char *path);
	void Animate(float start,float end,float speed);
	inline void Render() { this->mesh->Render(); }
	inline vector<Matrix4f> GiveTransform() { return this->transform; }




};

#endif