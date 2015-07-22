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




	if (ctrl->GetDropFiles().size() > 0)
	{

		try
		{


			std::string copied_folder_path = "data\\objects\\";
			std::string entity_name = ctrl->GetDropFiles()[0].substr(ctrl->GetDropFiles()[0].find_last_of("\\") + 1);
			copied_folder_path += entity_name;


			AFile::copyDir(boost::filesystem::path(ctrl->GetDropFiles()[0]),
				boost::filesystem::path(copied_folder_path));


			InfoComponent * ic = new InfoComponent();
			ic->GetInfo()->base_rot = glm::vec3(0.0);
			ic->GetInfo()->base_scale = glm::vec3(1.0);
			ic->GetInfo()->entity_name = entity_name;
			ic->GetInfo()->cull = 1;
			ic->GetInfo()->affected_by_ssao = 1;
			ic->GetInfo()->radius = 12.5;

			boost::property_tree::write_xml(AString::char_to_str(std::string(copied_folder_path + "\\general_info.ainfo"))
				, ic->GetInfo()->GetPtree());


			delete ic;


			if (AFile::GetFileWithExtension(copied_folder_path, ".obj"))
			{
				AssimpConverter * ac = new AssimpConverter();
				ac->ConvertModel(AFile::GetFileWithExtension(copied_folder_path, ".obj"));
				delete ac;



				ResourceLoader * res = ctrl->GetGameObject()->GetResource();
				SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


				Entity * new_entity = new Entity();
				scene_info->AddComponentsToEntity(AString::char_to_str(copied_folder_path), new_entity);
				scene_info->AddEntity(new_entity);


			}
			else
				throw std::string("No model file detected!");


			ctrl->ResetDropList();


		}
		catch (std::string e)
		{
			std::cerr << e;
		}




	}


}


