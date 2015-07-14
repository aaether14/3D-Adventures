#include "mesh_drawer.hpp"





void MeshDrawer::Init(MeshShader * shader,Controller * ctrl)
{



	this->shader = shader;
	this->LoadMeshes(ctrl);



}




void MeshDrawer::Clean()
{



	if (this->c_manager)
	delete this->c_manager;



	if (this->s_manager)
	delete this->s_manager;



}




void MeshDrawer::LoadMeshes(Controller * ctrl)
{



	ResourceLoader * resource = ctrl->GetGameObject()->GetResource();



	this->s_manager = new StaticManager(ctrl);
	this->s_manager->Load(resource->GetStaticFile(), ctrl);




	this->c_manager = new CreatureManager();


	this->c_manager->GetPlayer()->LoadChar(resource->GetPlayerFile());
	this->c_manager->GetPlayer()->LoadWeap(resource->GetWeaponFile());
	this->c_manager->GetPlayer()->LoadMount(resource->GetMountFile());




	ctrl->GetCameraPointer()->GetInfo()->SetDistance(50.0f);


}




void MeshDrawer::Enable(Controller * ctrl)
{




	//this->c_manager->GetPlayer()->Enable(ctrl);
	s_manager->GetPalette()->ControlPalette(ctrl);
	s_manager->GetPalette()->PlacePalette(ctrl, s_manager->GetEntityInfos(), s_manager->GetEntities());


}




void MeshDrawer::Draw(Controller *ctrl){



    //this->c_manager->GetPlayer()->Render(ctrl, this->shader);


	shader->SetSpecular(0.0f, 1.0f);
    s_manager->Render(ctrl, this->shader);
	s_manager->GetPalette()->Render(ctrl, shader, s_manager->GetEntities());




}



/*


void MeshDrawer::TransformMesh(AnimatedMesh * mesh)
{


	for (GLuint i = 0; i <= mesh->GiveTransform().size(); i++) 
		this->SetBoneTransform(i, mesh->GiveTransform()[i]);



}



*/
