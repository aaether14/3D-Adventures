/*


Base component implementation
Interface for adding components to entities
Dependent on file's extension to determine it's actions


*/




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