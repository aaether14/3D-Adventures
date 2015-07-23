#include "granny_loader.hpp"




#define CHECKED_RELEASE(x) { if (x) { (x)->Release(); } (x) = NULL; } 0





GrannyTexture::GrannyTexture()  : Name(NULL), TextureName(0)
{



}

GrannyTexture::~GrannyTexture()
{


    if (TextureName != 0)
    {


        glDeleteTextures(1, &TextureName);
        TextureName = 0;



    }



    delete [] Name;
    Name = NULL;


}

GrannyMesh::GrannyMesh() : Mesh(NULL), MeshBinding(NULL), VertexBufferObject(0), IndexBufferObject(0)
{
   



}

GrannyMesh::~GrannyMesh()
{


	glDeleteBuffers(1, &VertexBufferObject);
	glDeleteBuffers(1, &IndexBufferObject);


	VertexBufferObject = 0;
	IndexBufferObject = 0;

    Mesh = NULL;
    MaterialBindings.clear();

    if (MeshBinding)
    {


        GrannyFreeMeshBinding(MeshBinding);
        MeshBinding = NULL;


    }



}

GrannyModelBinding::GrannyModelBinding()  : ModelInstance(NULL)
{




}

GrannyModelBinding::~GrannyModelBinding()
{



    if (ModelInstance)
    {


        GrannyFreeModelInstance(ModelInstance);
        ModelInstance = NULL;



    }



    for(granny_uint32x i = 0; i < BoundMeshes.size(); ++i)
    {


        delete BoundMeshes[i];
        BoundMeshes[i] = NULL;



    }

    BoundMeshes.clear();


}





GrannyScene::GrannyScene()
  : SceneFile(NULL),
    SceneFileInfo(NULL),
    SharedLocalPose(NULL),
    SharedWorldPose(NULL),
    MaxBoneCount(-1)

{
}





GrannyScene::~GrannyScene()
{
    for(granny_uint32x i = 0; i < Textures.size(); ++i)
    {



        delete Textures[i];
        Textures[i] = NULL;


    }

    for(granny_uint32x i = 0; i < Models.size(); ++i)
    {


        delete Models[i];
        Models[i] = NULL;



    }


    GrannyFreeLocalPose(SharedLocalPose);
    GrannyFreeWorldPose(SharedWorldPose);



    SharedLocalPose = NULL;
    SharedWorldPose = NULL;

    GrannyFreeFile(SceneFile);
    SceneFile = NULL;
    SceneFileInfo = NULL;


}




