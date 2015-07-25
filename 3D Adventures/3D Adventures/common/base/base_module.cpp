#include "base_module.hpp"



void AModule::SetManager(AModule * module)
{

	manager = module;

}




void AModule::Enable()
{


	std::map<std::string, AModule*>::iterator it;



	for (it = module_map.begin(); it != module_map.end(); it++)
		it->second->Enable();


}



void AModule::Clean()
{


	std::map<std::string, AModule*>::iterator it;



	for (it = module_map.begin(); it != module_map.end(); it++)
		it->second->Clean();


}