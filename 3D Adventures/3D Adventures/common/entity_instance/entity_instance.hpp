#ifndef ENTITY_INSTANCE_HPP
#define ENTITY_INSTANCE_HPP





#include <entity_info/transform_info.hpp>
#include <base/base_entity_instance.hpp>






class EntityInstance : public AEntityInstance
{




	boost::shared_ptr<TransformInfo> transform_info;



public:


	/**
	Get pointer to transform info
	*/
	inline TransformInfo * GetTransformInfo(){ return transform_info.get(); }
	/**
	Alloc data
	*/
	EntityInstance() : transform_info(new TransformInfo()){}



	/**
	Match interface and determine how instance affects scene
	*/
	void Enable(AModule * manager);




};





#endif