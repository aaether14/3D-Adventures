#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP




#include "controller_math.hpp"
#include <fstream>
#include <boost/filesystem.hpp>




namespace AFile
{


	template <class T>
	inline void WriteToFile(std::ofstream& os, const T& obj){ os.write((const char*)&(obj), sizeof(T)); }
	template <class T>
	inline void ReadFromFile(std::ifstream& is, const T& obj){ is.read((char*)&(obj), sizeof(T)); }




}




#endif