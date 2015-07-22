#include "scene_info.hpp"




void SceneInfo::AddComponentsToEntity(char * path, Entity * new_entity)
{



	boost::filesystem::directory_iterator iterator(path);
	for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
	{




		if (boost::filesystem::is_regular_file(iterator->path()))
		{





			ModelComponent * mc = new ModelComponent();
			if (mc->isValid(AString::char_to_str(boost::filesystem::extension(iterator->path()))))
			{
				mc->Load(AString::char_to_str(iterator->path().string()),
					AString::char_to_str(boost::filesystem::extension(iterator->path())));
				new_entity->AddComponent("ModelComponent", mc);
			}
			else
				if (mc)
					delete mc;




			InfoComponent * ic = new InfoComponent();
			if (ic->isValid(AString::char_to_str(boost::filesystem::extension(iterator->path()))))
			{
				ic->Load(AString::char_to_str(iterator->path().string()),
					AString::char_to_str(boost::filesystem::extension(iterator->path())));
				new_entity->AddComponent("InfoComponent", ic);
			}
			else if (ic)
				delete ic;



		}



	}


}




void SceneInfo::AddEntity(Entity * new_entity)
{

	if (new_entity)
		if (!new_entity->GetComponentsSize())
			delete new_entity;
		else
		{
			if (new_entity->GetComponent("InfoComponent"))
			{
				InfoComponent * ic = static_cast<InfoComponent*>(new_entity->GetComponent("InfoComponent"));
				if (!entity_map.count(ic->GetInfo()->entity_name))
					entity_map[ic->GetInfo()->entity_name] = new_entity;
				else
				{
					GLuint number_sufix = 2;
					while (entity_map.count(ic->GetInfo()->entity_name + std::to_string(number_sufix)))
						number_sufix++;
					ic->GetInfo()->entity_name = ic->GetInfo()->entity_name + std::to_string(number_sufix);
					entity_map[ic->GetInfo()->entity_name] = new_entity;

				}
			}
			else
			{
				const std::string &ex("No info component found");
				boost::system::error_code er;
				throw boost::filesystem::filesystem_error(ex, er);
			}
		}


}



void SceneInfo::Load()
{



	//reading components


	try
	{


		boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
		{
		


			Entity * new_entity = new Entity();
			AddComponentsToEntity(AString::char_to_str(iterator->path().string()), new_entity);
			AddEntity(new_entity);



		}


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
	std::cout << ex.what() << '\n';
	}





	//Reading infos




	using boost::property_tree::ptree;
	ptree pt;
	read_xml(GetPath(), pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
	{




		if (v.first == "GeneralInfo")
		{


		   map_size.x = v.second.get<float>("Width");
		   map_size.y = v.second.get<float>("Height");
		   number_of_tiles = v.second.get<int>("Tiles");
		   entity_infos = new std::vector<TransformInfo*>[number_of_tiles];



		}
		else if (v.first == "Entity")
		{


			TransformInfo * new_info = new TransformInfo();


			std::string base_position;
			std::string base_rotation;
			std::string base_scale;


			base_position = v.second.get<std::string>("Position");
			base_rotation = v.second.get<std::string>("Rotation");
			base_scale = v.second.get<std::string>("Scale");
			new_info->entity_name = v.second.get<std::string>("EntityName");


			new_info->pos = Math::GetVecFromString(base_position);
			new_info->rot = Math::GetVecFromString(base_rotation);
			new_info->scale = Math::GetVecFromString(base_scale);


			new_info->matrix = Math::Translation(new_info->pos)*
				Math::Rotate(new_info->rot)*
				Math::Scale(new_info->scale);


			GLuint ind = GLuint(new_info->pos.z / (map_size.y / sqrt(number_of_tiles)))*sqrt(number_of_tiles) + 
				GLuint(new_info->pos.x / (map_size.x / sqrt(number_of_tiles)));


			GetEntityInfos()[ind].push_back(new_info);


		}




	}



	SetShouldReset(true);


}




void SceneInfo::Save()
{




	using boost::property_tree::ptree;
	ptree pt;
	ptree rootNode;




	{

		ptree new_info;
		new_info.push_back(ptree::value_type("Width", ptree(std::to_string(map_size.x))));
		new_info.push_back(ptree::value_type("Height", ptree(std::to_string(map_size.y))));
		new_info.push_back(ptree::value_type("Tiles", ptree(std::to_string(number_of_tiles))));
		rootNode.add_child("GeneralInfo", new_info);

	}




	for (GLuint i = 0; i < number_of_tiles; i++)
	{


		for (GLuint j = 0; j < GetEntityInfos()[i].size(); j++)
		{


			TransformInfo * info = GetEntityInfos()[i][j];


			ptree new_info;
			new_info.push_back(ptree::value_type("Position", ptree(Math::GetStringFromVec(info->pos))));
			new_info.push_back(ptree::value_type("Rotation", ptree(Math::GetStringFromVec(info->rot))));
			new_info.push_back(ptree::value_type("Scale", ptree(Math::GetStringFromVec(info->scale))));
			new_info.push_back(ptree::value_type("EntityName", ptree(info->entity_name)));
			rootNode.add_child("Entity", new_info);

		}

	}


	pt.add_child("Scene", rootNode);
	boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
	write_xml(GetPath(), pt, std::locale(), settings);




}




void SceneInfo::Reset()
{



}




void SceneInfo::InsertNewEntity(std::string path)
{

	try
	{


		std::string copied_folder_path = "data\\objects\\";
		std::string entity_name = path.substr(path.find_last_of("\\") + 1);
		copied_folder_path += entity_name;


		if (AFile::copyDir(boost::filesystem::path(path),
			boost::filesystem::path(copied_folder_path)))
		{

			InfoComponent * ic = new InfoComponent();
			ic->GetInfo()->base_rot = glm::vec3(0.0);
			ic->GetInfo()->base_scale = glm::vec3(1.0);
			ic->GetInfo()->entity_name = entity_name;
			ic->GetInfo()->cull = 1;
			ic->GetInfo()->affected_by_ssao = 1;
			ic->GetInfo()->radius = 12.5;



			boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
			boost::property_tree::write_xml(AString::char_to_str(std::string(copied_folder_path + "\\general_info.ainfo"))
				, ic->GetInfo()->GetPtree(), std::locale(), settings);


			delete ic;


			if (AFile::GetFileWithExtension(copied_folder_path, ".obj"))
			{
				AssimpConverter * ac = new AssimpConverter();
				ac->ConvertModel(AFile::GetFileWithExtension(copied_folder_path, ".obj"));
				delete ac;



				Entity * new_entity = new Entity();
				AddComponentsToEntity(AString::char_to_str(copied_folder_path), new_entity);
				AddEntity(new_entity);


			}
			else
				throw std::string("No model file detected!");

		}
		else
			throw std::string("Could not create entity - most likely there's another entity with the same name!");



	}
	catch (std::string e)
	{
		std::cerr << e;
	}


}

