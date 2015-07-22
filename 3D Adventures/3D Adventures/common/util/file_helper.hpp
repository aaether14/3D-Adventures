/*


Using Templates for easier binary data storing/loading


*/



#ifndef FILE_HELPER_HPP
#define FILE_HELPER_HPP




#include "math_helper.hpp"
#include "string_helper.hpp"
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>




namespace AFile
{


	template <class T>
	inline void WriteToFile(std::ofstream& os, const T& obj){ os.write((const char*)&(obj), sizeof(T)); }
	template <class T>
	inline void ReadFromFile(std::ifstream& is, const T& obj){ is.read((char*)&(obj), sizeof(T)); }


	bool copyDir(
		boost::filesystem::path const & source,
		boost::filesystem::path const & destination
		);


	char *GetFileWithExtension(std::string path, std::string extension);


}




#endif