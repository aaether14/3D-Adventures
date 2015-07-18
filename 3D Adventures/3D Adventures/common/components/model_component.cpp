#include "model_component.hpp"





bool ModelComponent::isValid(char * extension)
{


	std::vector<std::string> valid_extensions = { ".aao", ".gr2" };

	for (GLuint i = 0; i < valid_extensions.size(); i++)
		if (!std::string(extension).compare(valid_extensions[i]))
			return true;

		return false;


}



void ModelComponent::Load(char * path, char * extension)
{


	if (!std::string(extension).compare(".gr2"))
	{
		GrannyModel * md = new GrannyModel();
		md->Load(AString::char_to_str(path));
		model = static_cast<AModel*>(md);
	}
	if (!std::string(extension).compare(".aao"))
	{
		Aa_model * md = new Aa_model();
		md->Load(AString::char_to_str(path));
		model = static_cast<AModel*>(md);
	}


}