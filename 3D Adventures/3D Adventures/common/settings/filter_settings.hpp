#ifndef FILTER_SETTINGS_HPP
#define FILTER_SETTINGS_HPP




#include <util/controller_math.hpp>
#include <util/file_helper.hpp>




class FilterSettings
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




	GLboolean should_reset;



	inline FilterSettings(){ this->Init(); }
	void Init();



	inline ~FilterSettings(){ this->Clean(); }
	void Clean();



	void Reset();
	void Save(char*path);
	void Load(char*path);



};




#endif