#include "scene_info.hpp"




void SceneInfo::Load()
{





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




}




void SceneInfo::Save()
{



}




void SceneInfo::Reset()
{



}


