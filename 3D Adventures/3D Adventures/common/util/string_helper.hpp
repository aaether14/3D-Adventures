#ifndef STRING_HELPER_HPP
#define STRING_HELPER_HPP



#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>





/**
Useful functions regarding strings
*/
namespace AString
{


	/**
	Load a file to a string
	*/
	std::string LoadFileToString(char * path);
	/**
	Succesfully converts std::string to char*
	*/
	char * char_to_str(std::string str);




}




#endif