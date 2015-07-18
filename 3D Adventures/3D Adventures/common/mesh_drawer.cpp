#include "mesh_drawer.hpp"





void MeshDrawer::Init(MeshShader * shader,Controller * ctrl)
{



	this->shader = shader;
	this->LoadMeshes(ctrl);



}




void MeshDrawer::Clean()
{



	if (this->s_manager)
	delete this->s_manager;



}




void MeshDrawer::LoadMeshes(Controller * ctrl)
{



	s_manager = new StaticManager(ctrl);




}




void MeshDrawer::Enable(Controller * ctrl)
{



	s_manager->GetPalette()->ControlPalette(ctrl);
	s_manager->GetPalette()->PlacePalette(ctrl);


}




void MeshDrawer::Draw(Controller *ctrl){



	shader->SetSpecular(0.0f, 1.0f);
    s_manager->Render(ctrl, shader);
	s_manager->GetPalette()->Render(ctrl, shader);




}


