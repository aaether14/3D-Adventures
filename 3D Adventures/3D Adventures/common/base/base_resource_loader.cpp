#include "resource_loader.hpp"





void BaseResourceLoader::SaveChanges()
{


	try
	{

		std::map<std::string, AModule*>::iterator it;



		for (it = GetModuleMap().begin(); it != GetModuleMap().end(); it++)
			static_cast<AStateSaver*>(it->second)->Save();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}


}



void BaseResourceLoader::LoadChanges()
{



	printf("Debug....!!!!!\n");



	try
	{

		std::map<std::string, AModule*>::iterator it;



		for (it = GetModuleMap().begin(); it != GetModuleMap().end(); it++)
			printf("hello!\n");


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

		std::map<std::string, AModule*>::iterator it;



		for (it = GetModuleMap().begin(); it != GetModuleMap().end(); it++)
			static_cast<AStateSaver*>(it->second)->Reset();


	}
	catch (const boost::filesystem::filesystem_error& ex)
	{
		std::cerr << ex.what();
	}




}




void BaseResourceLoader::Init()
{



}




void BaseResourceLoader::Clean()
{



}




void BaseResourceLoader::Enable()
{



}




