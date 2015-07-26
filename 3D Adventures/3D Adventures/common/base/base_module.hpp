#ifndef BASE_MODEL_HPP
#define BASE_MODEL_HPP




#include <map>
#include <string>



/**
Interface for modules
*/
class AModule
{


private:


	std::map < std::string, AModule* > module_map;
	AModule * manager;


public:

	/**
	Add 'module' to 'key'
	*/
	inline void Add(std::string key, AModule*module){ module_map[key] = module; module->SetManager(GetManager()); module->Init(); }
	/**
	Get module from 'key'
	*/
	AModule * Get(std::string key){ return module_map[key]; }


	/**
	Determine how the module affects the engine
	*/
	virtual void Enable() = 0;
	/**
	Clean data
	*/
	virtual void Clean() = 0;
	/**
	Initialize data
	*/
	virtual void Init() = 0;
	/**
	Get manager
	*/
	AModule * GetManager(){ return manager; }


protected:


	/**
	Set manager of module
	*/
	virtual void SetManager(AModule * module);


};





#endif