#ifndef GRANNY_LOADER_HPP
#define GRANNY_LOADER_HPP



#include <granny.h>
#include <texture/texture.hpp>
#include <util/math_helper.hpp>
#include <base/base_model_loader.hpp>




using namespace std;



#define Offset(type, member) (&(((type*)NULL)->member))
#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4



#define TEX_DIR "data/model_textures/"
#pragma warning(disable : 4505)	




struct GrannyTexture
{


    char* Name;
    GLuint TextureName;
    GrannyTexture();
    ~GrannyTexture();



};

struct GrannyMesh
{



    granny_mesh* Mesh;
    granny_mesh_binding* MeshBinding;


    std::vector<GrannyTexture*> MaterialBindings;
    GLuint VertexBufferObject;
    GLuint IndexBufferObject;


    GrannyMesh();
    ~GrannyMesh();



};

struct GrannyModelBinding
{



    granny_model_instance* ModelInstance;
	GrannyModelBinding* AttachedTo;


	GLint BaseModelBone;
	GLint AttachModelBone;


    std::vector<GrannyMesh*> BoundMeshes;
	granny_real32 InitialMatrix[16];


    GrannyModelBinding();
    ~GrannyModelBinding();



};



struct GrannyScene
{



    granny_file      *SceneFile;
    granny_file_info *SceneFileInfo;


    std::vector<GrannyTexture*> Textures;
    std::vector<GrannyModelBinding*>   Models;

	
	
	granny_int32x      MaxBoneCount;
    granny_local_pose* SharedLocalPose;
    granny_world_pose* SharedWorldPose;




    GrannyScene();
    ~GrannyScene();


};





/**


Granny SDK implementation


*/
class GrannyModel : public AModel
{


#define MAX_BONES 128


	GLuint m_VAO;
    GrannyScene GlobalScene;
	std::vector<granny_control*> GrannyControls;
	granny_matrix_4x4 CompositeBuffer[MAX_BONES+1];
	granny_system_clock GlobalStartClock;



	GrannyMesh* CreateBoundMesh(granny_mesh* g_mesh, granny_model_instance* ModelInstance);


	bool CreateDemoTextures();
	bool CreateDemoModels();
	bool CreateSharedPoses();
	void RenderModel(GrannyModelBinding*,GLuint anim_num);
	void RenderMeshBindings(GrannyModelBinding* Model, granny_world_pose* Pose);



public:


	inline GrannyModel() { this->Init(); }
	GLint Init();


	int Load(const char* path);
	inline void Render(){ Render(-1); }
	void Clean();



	void LoadAnimation(const char*path);
	void PlayAnimation(GLuint index, GLuint loop_count);


	void AttachGrannyModel(GrannyModel*GrannyAttachModel, const char*bone_name);



	void Render(GLuint anim_num);
	void RenderAttachedModel(GrannyModel *AttachedGrannyModel);
	void Update(granny_real32 const CurrentTime);



	inline granny_matrix_4x4 *GiveTransform(){ return this->CompositeBuffer; }
	inline GLuint GetNumBones(){ return this->GlobalScene.MaxBoneCount; }



};





void print_matrix(granny_matrix_4x4 m);
granny_animation* GrannyLoadAnimation(const char* path);





#endif
