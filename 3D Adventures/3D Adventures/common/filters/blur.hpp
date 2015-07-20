/*


Basic gaussian blur and logarithmic blur


*/




#ifndef BLUR_HPP
#define BLUR_HPP




#include <shader/shader.hpp>
#include <texture/texture.hpp>
#include <util/math_helper.hpp>





class BlurImplementation
{



	Shader * gaus_blur1;
	Shader * gaus_blur2;




public:




	inline BlurImplementation(){ this->Init(); }
	void Init();



	inline ~BlurImplementation(){ this->Clean(); }
	void Clean();



	inline Shader * GetGausBlur1(){ return this->gaus_blur1; }
	inline Shader * GetGausBlur2(){ return this->gaus_blur2; }



	inline void BindGausBlurTexture1(){ this->gaus_blur1->Set("texture", 0); }
	inline void BindGausBlurTexture2(){ this->gaus_blur2->Set("texture", 0); }



	inline void SetBlurScale1(glm::vec3 scale){ this->gaus_blur1->Set("blur_scale", scale); }
	inline void SetBlurScale2(glm::vec3 scale){ this->gaus_blur2->Set("blur_scale", scale); }





};




#endif