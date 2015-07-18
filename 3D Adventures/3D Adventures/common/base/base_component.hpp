#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP





class AComponent
{

private:


protected:


public:


	virtual bool isValid(char * extension) = 0;
	virtual void Load(char * path, char * extension) = 0;



};



#endif