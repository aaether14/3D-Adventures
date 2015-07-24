#include "file_helper.hpp"





namespace AFile
{


	bool copyDir(
		boost::filesystem::path const & source,
		boost::filesystem::path const & destination
		)
	{
		namespace fs = boost::filesystem;
		try
		{
			// Check whether the function call is valid
			if (
				!fs::exists(source) ||
				!fs::is_directory(source)
				)
			{
				std::cerr << "Source directory " << source.string()
					<< " does not exist or is not a directory." << '\n'
					;
				return false;
			}
			if (fs::exists(destination))
			{
				std::cerr << "Destination directory " << destination.string()
					<< " already exists." << '\n'
					;
				return false;
			}
			// Create the destination directory
			if (!fs::create_directory(destination))
			{
				std::cerr << "Unable to create destination directory"
					<< destination.string() << '\n'
					;
				return false;
			}
		}
		catch (fs::filesystem_error const & e)
		{
			std::cerr << e.what() << '\n';
			return false;
		}
		// Iterate through the source directory
		for (
			fs::directory_iterator file(source);
			file != fs::directory_iterator(); ++file
			)
		{
			try
			{
				fs::path current(file->path());
				if (fs::is_directory(current))
				{
					// Found directory: Recursion
					if (
						!copyDir(
						current,
						destination / current.filename()
						)
						)
					{
						return false;
					}
				}
				else
				{
					// Found file: Copy
					fs::copy_file(
						current,
						destination / current.filename()
						);
				}
			}
			catch (fs::filesystem_error const & e)
			{
				std::cerr << e.what() << '\n';
			}
		}
		return true;
	}



	std::string GetFileWithExtension(std::string path, std::string extension)
	{


		boost::filesystem::directory_iterator iterator(path);
		for (; iterator != boost::filesystem::directory_iterator(); ++iterator)
			if (boost::filesystem::is_regular_file(iterator->path()))
				if (!extension.compare(boost::filesystem::extension(iterator->path())))
					return iterator->path().string();

		return STRING_ERROR;


	}



}