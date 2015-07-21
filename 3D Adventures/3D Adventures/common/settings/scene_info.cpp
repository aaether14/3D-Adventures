#include "scene_info.hpp"




void SceneInfo::Load()
{



	//reading components


	try
	{



		boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));


		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
		{
		


			Entity * new_entity = new Entity();



	boost::filesystem::directory_iterator iterator2(iterator->path());
	for (; iterator2 != boost::filesystem::directory_iterator(); ++iterator2)
	{




		if (boost::filesystem::is_regular_file(iterator2->path()))
		{





			ModelComponent * mc = new ModelComponent();
			if (mc->isValid(AString::char_to_str(boost::filesystem::extension(iterator2->path()))))
			{
				mc->Load(AString::char_to_str(iterator2->path().string()),
					AString::char_to_str(boost::filesystem::extension(iterator2->path())));
				new_entity->AddComponent("ModelComponent", mc);
			}
			else
				if (mc)
					delete mc;



			InfoComponent * ic = new InfoComponent();
			if (ic->isValid(AString::char_to_str(boost::filesystem::extension(iterator2->path()))))
			{
				ic->Load(AString::char_to_str(iterator2->path().string()),
					AString::char_to_str(boost::filesystem::extension(iterator2->path())));
				new_entity->AddComponent("InfoComponent", ic);
			}
			else if (ic)
				delete ic;



		}



	}




	if (new_entity)
	if (!new_entity->GetComponentsSize())
			delete new_entity;
	else
	{
		if (new_entity->GetComponent("InfoComponent"))
		{
			InfoComponent * ic = static_cast<InfoComponent*>(new_entity->GetComponent("InfoComponent"));
			if (!entity_map.count(ic->GetInfo()->name))
				entity_map[ic->GetInfo()->name] = new_entity;
		}
	}







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
	write_xml(GetPath(), pt);




}




void SceneInfo::Reset()
{



}


