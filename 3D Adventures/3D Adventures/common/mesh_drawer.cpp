#include "mesh_drawer.hpp"





void MeshDrawer::Init(MeshShader * shader,Controller * ctrl)
{



	this->shader = shader;
	this->LoadMeshes(ctrl);



}




void MeshDrawer::Clean()
{



	if (entity_manager)
	delete entity_manager;



}




void MeshDrawer::LoadMeshes(Controller * ctrl)
{



	entity_manager = new EntityManager(ctrl);




}




void MeshDrawer::Enable(Controller * ctrl)
{



	entity_manager->GetPalette()->ControlPalette(ctrl);
	entity_manager->GetPalette()->PlacePalette(ctrl);


}




void MeshDrawer::Draw(Controller *ctrl){



	shader->SetSpecular(0.0f, 1.0f);
    entity_manager->Render(ctrl, shader);
	entity_manager->GetPalette()->Render(ctrl, shader);




}


