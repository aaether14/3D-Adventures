#ifndef LIGHT
#define LIGHT




#include <shader/shader.hpp>
#include <util/controller_math.hpp>



#define MAX_POINT_LIGHTS 2
#define MAX_SPOT_LIGHTS 2




class Light
{



	
	Shader * shader;




	void InitDirectionalLight();
	void InitPointLights();
	void InitSpotLights();
	void InitFog();




public:



	Light();
	Light(Shader * shader);
	void Init(Shader * shader);


	inline ~Light(){ this->Clean(); }

	void Clean();


	void SetLight(glm::vec3 color, glm::vec3 direction ,float a_intensity, float d_intensity);
	void SetPointLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp);
	void SetSpotLights(int Index, glm::vec3 color, glm::vec3 position, float a_intensity, float d_intensity, float constant, float linear, float exp, glm::vec3 direction, GLfloat Cutoff);
	void SetFog(glm::vec3 color, GLfloat density);


};

#endif