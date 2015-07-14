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





namespace AString
{



	std::string LoadFileToString(char * path);
	char * char_to_str(std::string str);



}




#endif