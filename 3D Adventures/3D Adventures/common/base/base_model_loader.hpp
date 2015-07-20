/*


Base model loader implementation
Interface for adding any type of 3d model to an entity


*/



#ifndef BASE_MODEL_LOADER_HPP
#define BASE_MODEL_LOADER_HPP




class AModel
{


public:


	virtual int Load(const char * path) = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;


};




#endif