#ifndef BASE_MODULE_HPP
#define BASE_MODULE_HPP



#include <map>
#include <string>




/**
Interface for defining an engine's module
*/
class AModule
{


	std::map<std::string, AModule*> module_map;
	AModule * manager;


public:


	/**
	Get module stored with 'key'
	*/
	inline AModule * Get(std::string key){ return module_map[key]; }
	/**
	Store 'module' to 'key'
	*/
	inline AModule * Add(std::string key, AModule * module){ module_map[key] = module; module->SetManager(this); return module; }
	/**
	Get pointer of manager
	*/
	inline AModule * GetManager(){ return manager; }





protected:



	/**
	Determines how the module will affect the engine
	*/
	virtual void Enable();
	/**
	Clean data
	*/
	virtual void Clean();

	/**
	Each module can have a manager that holds the reference to other modules
	*/
	virtual void SetManager(AModule * module);



private:


};



#endif