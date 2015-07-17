#include "scene_info.hpp"




void SceneInfo::Load()
{





	try
	{

	boost::filesystem::directory_iterator iterator(std::string(OBJECT_FOLDER));

	for (; iterator != boost::filesystem::directory_iterator(); ++iterator)

	{



	boost::filesystem::directory_iterator iterator2(iterator->path());

	for (; iterator2 != boost::filesystem::directory_iterator(); ++iterator2)

	{




		if (boost::filesystem::is_regular_file(iterator2->path()))
			if (boost::filesystem::extension(iterator2->path()) == ".aao")
			{


			StaticEntity * new_entity = new StaticEntity();
			Aa_model * new_model = new Aa_model();
			new_model->Load(AString::char_to_str(iterator2->path().string()));
			new_entity->AddModelComponent(new_model);

			entities.push_back(new_entity);


			}
		else if (boost::filesystem::extension(iterator2->path()) == ".gr2")
		{


			StaticEntity * new_entity = new StaticEntity();
			GrannyModel * new_model = new GrannyModel();
			new_model->Load(AString::char_to_str(iterator2->path().string()));
			new_entity->AddModelComponent(new_model);

			entities.push_back(new_entity);


		}






	}






	}

	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
	std::cout << ex.what() << '\n';
	}




	printf("%i\n", entities.size());
}




void SceneInfo::Save()
{



}




void SceneInfo::Reset()
{



}