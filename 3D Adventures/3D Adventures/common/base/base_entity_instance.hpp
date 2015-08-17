#ifndef BASE_ENTITY_INSTANCE_HPP
#define BASE_ENTITY_INSTANCE_HPP




#include <boost/smart_ptr.hpp>
#include "base_module.hpp"




class AEntityInstance
{


public:


	/**
	Every instance should have a way to affect scene
	*/
	virtual void Enable(AModule * manager) = 0;
	/**
	Get vector of child nodes
	*/
	inline std::vector<boost::shared_ptr<AEntityInstance>> GetChildNodes(){ return child_nodes; }



private:



	std::vector<boost::shared_ptr<AEntityInstance>> child_nodes;



protected:



};



#endif