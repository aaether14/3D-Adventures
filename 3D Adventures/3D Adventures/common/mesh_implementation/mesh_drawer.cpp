#include "mesh_drawer.hpp"





void MeshDrawer::Init()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	entity_manager = new EntityManager(ctrl);



}




void MeshDrawer::Clean()
{



	if (entity_manager)
	delete entity_manager;



}






void MeshDrawer::Enable()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	entity_manager->GetPalette()->ControlPalette(ctrl);
	entity_manager->GetPalette()->PlacePalette(ctrl);





}




void MeshDrawer::Render()
{



	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	MeshShader * shader = static_cast<MeshShader*>((GetManager()->Get("Pipeline"))->Get("MeshWrapper"));



	shader->SetSpecular(0.0f, 1.0f);
	if (ctrl->GetGameObject()->GetTechniques()->GetShadow()->OnShadowPass())
	{
		glCullFace(GL_FRONT);
		entity_manager->Render(ctrl, shader);
		entity_manager->GetPalette()->Render(ctrl, shader);
		glCullFace(GL_BACK);
	}
	else
	{
		entity_manager->Render(ctrl, shader);
		entity_manager->GetPalette()->Render(ctrl, shader);
	}









}


