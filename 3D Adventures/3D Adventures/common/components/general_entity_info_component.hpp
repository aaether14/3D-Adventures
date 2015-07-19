#ifndef GENERAL_ENTITY_INFO_COMPONENT
#define GENERAL_ENTITY_INFO_COMPONENT





#include <base/base_component.hpp>
#include <util/file_helper.hpp>
#include <util/controller_math.hpp>





class InfoComponent : public AComponent
{



	class GeneralEntityInfo
	{


	public:


		glm::vec3 base_rot;
		glm::vec3 base_scale;
		GLboolean affected_by_ssao;


		void Read(std::ifstream & is);
		



	}*info;
	


public:



	inline InfoComponent(){ Init(); }
	void Init();


	bool isValid(char * extension);
	void Load(char * path, char * extension);



	GeneralEntityInfo * GetInfo(){ return info; }



};





#endif