#include "resource_loader.hpp"





void BaseResourceLoader::SaveChanges()
{


	std::map<std::string, AStateSaver*>::iterator it;


	
	for (it = state_changers.begin(); it != state_changers.end(); it++)
		it->second->Save();

}



void BaseResourceLoader::LoadChanges()
{


	std::map<std::string, AStateSaver*>::iterator it;



	for (it = state_changers.begin(); it != state_changers.end(); it++)
		it->second->Load();

}




