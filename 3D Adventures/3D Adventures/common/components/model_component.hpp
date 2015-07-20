/*


Model component implementation
Used to load any type of model that has Render, Load and Clean functions defined


*/




#ifndef MODEL_COMPONENT_HPP
#define MODEL_COMPONENT_HPP





#include <model_loaders/aaether_loader.hpp>
#include <model_loaders/granny_loader.h>
#include <util/file_helper.hpp>
#include <util/string_helper.hpp>
#include <base/base_component.hpp>
#include <base/base_model_loader.hpp>





class ModelComponent : public AComponent
{


	AModel * model;


public:


	bool isValid(char * extension);
	void Load(char * path, char * extension);


	inline AModel*GetModel(){ return model; }



};




#endif