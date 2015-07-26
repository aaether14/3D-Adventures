#include "controls.hpp"







void Controller::Init()
{



	using boost::property_tree::ptree;
	ptree pt;
	read_xml("settings.xml", pt);




	BOOST_FOREACH(ptree::value_type const& v, pt.get_child("GeneralInfo"))
	{




		if (v.first == "BaseInfo")
		{


			GLuint window_width = v.second.get<GLuint>("WindowWidth");
			GLuint window_height = v.second.get<GLuint>("WindowHeight");
			std::string window_title = v.second.get<std::string>("WindowTitle");
			GLboolean fullscreen = v.second.get<GLboolean>("Fullscreen");
			GLuint opengl_major_version = v.second.get<GLuint>("OpenGLMajorVersion");
			GLuint opengl_minor_version = v.second.get<GLuint>("OpenGLMinorVersion");
			std::string project_name = v.second.get<std::string>("ProjectName");




			CreateWindow(window_width, window_height, fullscreen, AString::char_to_str(window_title), opengl_major_version, opengl_minor_version);
			camera = new Camera();
			g_obj = new GameObject(GetWindowWidth(), GetWindowHeight());




			ResourceLoader * res = g_obj->GetResource();
			res->LoadResourcePaths(AString::char_to_str(project_name));
			res->Add("Environment", new Environment(res->GetEnvFile()));
			res->Add("FilterSettings", new FilterSettings(res->GetFSettingsFile()));
			res->Add("Entities", new SceneInfo(res->GetSceneFile()));
			res->LoadChanges();





		}
		



	}





	

}





void Controller::Clean()
{

	
	if (camera)
	delete camera;


	if (g_obj)
	delete g_obj;


	ControllerSource::Clean();


}






void Controller::Enable()
{



	ControllerSource::Enable();

	camera->ProcessInput(this);
	camera->ComputeAngles(this);
	camera->SetFrustum(camera->GetView()->getCamera());




	if (GetDropFiles().size() > 0)
	{


		ResourceLoader * res = GetGameObject()->GetResource();
		SceneInfo * scene_info = static_cast<SceneInfo*>(res->Get("Entities"));


		scene_info->InsertNewEntity(GetDropFiles()[0]);
		ResetDropList();


	}




}
