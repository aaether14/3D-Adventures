#include "general_entity_info_component.hpp"





bool InfoComponent::isValid(char * extension)
{


	//See if valid extension


	if (!std::string(extension).compare(".ainfo"))
		return true;
	return false;


}




void InfoComponent::Load(char * path, char* extension)
{

	//Read if valid file

	info->Read(std::ifstream(path));



}




void InfoComponent::Init()
{


	info = new GeneralEntityInfo();


}




void InfoComponent::GeneralEntityInfo::Read(std::ifstream & is)
{


	//read xml using boost


	using boost::property_tree::ptree;
	ptree pt;
	read_xml(is, pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("GeneralInfo"))
	{


		if (v.first == "BaseInfo")
		{



			std::string base_rot;
			std::string base_scale;


			base_rot = v.second.get<std::string>("Rotation");
			base_scale = v.second.get<std::string>("Scale");
			affected_by_ssao = v.second.get<GLboolean>("SSAO");
			cull = v.second.get<GLboolean>("Cull");
			radius = v.second.get<GLfloat>("Radius");
			name = v.second.get<std::string>("Name");



			this->base_rot = Math::GetVecFromString(base_rot);
			this->base_scale = Math::GetVecFromString(base_scale);


		}


		break;

	}

}