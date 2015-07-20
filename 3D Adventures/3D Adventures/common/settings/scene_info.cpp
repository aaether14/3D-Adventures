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
			entities.push_back(new_entity);




	}




	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
	std::cout << ex.what() << '\n';
	}





	//Reading infos




	using boost::property_tree::ptree;
	ptree pt;
	read_xml("testXml.xml", pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("Scene"))
	{


		if (v.first == "Entity")
		{


			TransformInfo * new_info = new TransformInfo();


			std::string base_position;
			std::string base_rotation;
			std::string base_scale;


			base_position = v.second.get<std::string>("Position");
			base_rotation = v.second.get<std::string>("Rotation");
			base_scale = v.second.get<std::string>("Scale");
			new_info->id = v.second.get<int>("Id");


			new_info->pos = Math::GetVecFromString(base_position);
			new_info->rot = Math::GetVecFromString(base_rotation);
			new_info->scale = Math::GetVecFromString(base_scale);


			Math::print_vec3(new_info->rot);

			delete new_info;


		}




	}





}




void SceneInfo::Save()
{




	using boost::property_tree::ptree;
	ptree pt;
	ptree rootNode;


	for (GLuint i = 0; i < number_of_tiles; i++)
	{


		for (GLuint j = 0; j < GetEntityInfos()[i].size(); j++)
		{


			TransformInfo * info = GetEntityInfos()[i][j];


			ptree new_info;
			new_info.push_back(ptree::value_type("Position", ptree(Math::GetStringFromVec(info->pos))));
			new_info.push_back(ptree::value_type("Rotation", ptree(Math::GetStringFromVec(info->rot))));
			new_info.push_back(ptree::value_type("Scale", ptree(Math::GetStringFromVec(info->scale))));
			new_info.push_back(ptree::value_type("Id", ptree(std::to_string(info->id))));
			rootNode.add_child("Entity", new_info);

		}

	}


	pt.add_child("Scene", rootNode);
	write_xml("testXml.xml", pt);




}




void SceneInfo::Reset()
{



}


