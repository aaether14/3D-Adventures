#include "resource_loader.hpp"





void BaseResourceLoader::SaveChanges()
{


	try
	{

		std::map<std::string, AStateSaver*>::iterator it;



		for (it = state_changers.begin(); it != state_changers.end(); it++)
			it->second->Save();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}


}



void BaseResourceLoader::LoadChanges()
{


	try
	{


		std::map<std::string, AStateSaver*>::iterator it;



		for (it = state_changers.begin(); it != state_changers.end(); it++)
			it->second->Load();



	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}




}



void BaseResourceLoader::NoChanges()
{


	try
	{


		std::map<std::string, AStateSaver*>::iterator it;



		for (it = state_changers.begin(); it != state_changers.end(); it++)
			it->second->Reset();



	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}


}




