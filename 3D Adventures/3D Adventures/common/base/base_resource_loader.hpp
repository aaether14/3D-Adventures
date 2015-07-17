#ifndef BASE_RESOURCE_LOADER_HPP
#define BASE_RESOURCE_LOADER_HPP




#include <util/string_helper.hpp>
#include <util/controller_math.hpp>
#include <base/base_state_saver.hpp>
#include <map>
using namespace::AString;





class BaseResourceLoader
{


private:


	std::map < std::string, AStateSaver * > state_changers;


protected:


	inline std::map < std::string, AStateSaver * >GetStateChangers(){ return state_changers; }



public:




	inline void Add(std::string name, AStateSaver* state_changer){ state_changers[name] = state_changer; }
	inline AStateSaver* Get(std::string name){ return state_changers[name]; }



	void SaveChanges();
	void LoadChanges();




};





#endif