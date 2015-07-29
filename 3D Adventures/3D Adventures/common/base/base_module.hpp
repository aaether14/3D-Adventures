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
	virtual void Add(std::string key, AModule*module);
	/**
	Get module from 'key'
	*/
	virtual AModule * Get(std::string key);



	/**
	Determine how module affects engine
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
	virtual AModule * GetManager();


protected:


	/**
	Set manager of module
	*/
	virtual void SetManager(AModule * module);
	/**
	Standardized cleaning routine
	*/
	virtual void CleanModule();


};





#endif