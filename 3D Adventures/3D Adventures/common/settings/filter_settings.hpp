#ifndef FILTER_SETTINGS_HPP
#define FILTER_SETTINGS_HPP




#include <util/controller_math.hpp>
#include <util/file_helper.hpp>
#include "../base//base_state_saver.hpp"




class FilterSettings : public AStateSaver
{



public:


	struct SSAOData
	{

		GLboolean Enabled;
		GLfloat Radius;
		GLfloat Power;
		GLint NumSamples;
	}SSAO;


	struct DoFData
	{
		GLboolean Enabled;
	}DoF;



	struct HDRData
	{

		struct BloomData
		{
			GLboolean Enabled;
			GLfloat Whitepoint;
		}Bloom;

	}HDR;



	struct FXAAData
	{

		GLboolean Enabled;
		GLfloat span_max;
		GLfloat reduce_min;
		GLfloat reduce_mul;

	}FXAA;





	inline FilterSettings(char * path){ this->Init(path); }
	void Init(char *path);




	void Reset();
	void Save();
	void Load();



};




#endif