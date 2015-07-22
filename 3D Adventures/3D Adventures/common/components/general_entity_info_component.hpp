/*


Info component implementation
Affects entity


*/



#ifndef GENERAL_ENTITY_INFO_COMPONENT
#define GENERAL_ENTITY_INFO_COMPONENT





#include <base/base_component.hpp>
#include <util/file_helper.hpp>
#include <util/math_helper.hpp>





class InfoComponent : public AComponent
{



	class GeneralEntityInfo
	{


	public:


		std::string entity_name;
		glm::vec3 base_rot;
		glm::vec3 base_scale;
		GLfloat radius;
		GLboolean affected_by_ssao;
		GLboolean cull;


		void Read(std::ifstream & is);
		boost::property_tree::ptree GetPtree();
		



	}*info;
	


public:



	inline InfoComponent(){ Init(); }
	void Init();


	bool isValid(char * extension);
	void Load(char * path, char * extension);



	GeneralEntityInfo * GetInfo(){ return info; }



};





#endif