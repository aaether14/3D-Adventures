#ifndef BASE_RESOURCE_LOADER_HPP
#define BASE_RESOURCE_LOADER_HPP




#include <util/file_helper.hpp>
#include <util/string_helper.hpp>
#include <util/math_helper.hpp>
#include <base/base_state_saver.hpp>
#include <map>
using namespace::AString;




/**


Can be derived to store any state changers
for centralised save/load


*/
class BaseResourceLoader
{


private:


	/**
	Storing state changers in a map
	*/
	std::map < std::string, AStateSaver * > state_changers;


protected:

	/**
	Map can only be accesed in classes that are deriving from this
	*/
	inline std::map < std::string, AStateSaver * >GetStateChangers(){ return state_changers; }


public:



	/**
	Map an instance of a state changer to a string
	*/
	inline void Add(std::string name, AStateSaver* state_changer){ state_changers[name] = state_changer; }
	/**
	Get a state changer based on it's key
	*/
	inline AStateSaver* Get(std::string name){ return state_changers[name]; }


	/**
	Iterates through all state changer map and use their save function
	*/
	void SaveChanges();
	/**
	Iterates through all state changer map and use their load function
	*/
	void LoadChanges();
	/**
	Iterates through all state changer map and use their reset function
	*/
	void NoChanges();



};





#endif