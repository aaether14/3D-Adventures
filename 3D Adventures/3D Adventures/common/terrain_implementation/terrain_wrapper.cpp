#include "terrain_wrapper.hpp"




void TerrainWrapper::Init()
{



	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	ResourceLoader * resource = ctrl->GetGameObject()->GetResource();


	terra = new Terrain();



	terra->LoadChunks(resource->GetTerrainFile());


	terra->LoadColorFiles(resource->GetColorFile(),
		resource->GetTFile(),
		resource->GetNFile(),
		resource->GetAFile());



	ctrl->GetGameObject()->SetTree(terra->GetTree());


}


void TerrainWrapper::ManagePlayerCollision(Controller*ctrl, bool null_gravity)
{



	GLfloat terrain_height = HeightAt(terra,
		ctrl->GetCameraPointer()->GetInfo()->getCameraPos().x,
		ctrl->GetCameraPointer()->GetInfo()->getCameraPos().z);



	if (ctrl->GetCameraPointer()->GetInfo()->getCameraPos().y < terrain_height)
		ctrl->GetCameraPointer()->GetInfo()->SetCameraY(terrain_height);


	if (!null_gravity)
		ctrl->GetCameraPointer()->GetInfo()->SetCameraY(terrain_height);


}



void TerrainWrapper::Enable()
{


	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	ManagePlayerCollision(ctrl, false);



	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));



	Shader::Enable();


	Set("myTextureSampler", 0);
	Set("myTextureSampler2", 1);
	Set("myTextureSampler3", 2);
	Set("shadow_map", 3);
	SendTextureAttributes(terra->GetTextureAttributes(), 4);



	getLight()->SetFog(glm::pow(env->fog_color, glm::vec3(2.2)), env->fog_density);



	getLight()->SetDirectionalLight(env->terrain_bright*
		glm::pow(env->sun_color, glm::vec3(2.2)),
		env->sun_dir,
		env->terrain_ambient,
		env->terrain_diffuse);



	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);





	Set("LightMatrix", biasMatrix*
		tech->GetShadow()->GetDirectionalShadow(env, info, view));



	tech->GetShadow()->GetShadowMap()->BindTexture(0, GL_TEXTURE3);
	tech->GetShadow()->GetShadowMap()->ResetTextureState();



}





void TerrainWrapper::Render()
{




	Controller * ctrl = static_cast<Controller*>(GetManager()->Get("Controller"));
	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	ResourceLoader * res = ctrl->GetGameObject()->GetResource();
	Environment * env = static_cast<Environment*>(res->Get("Environment"));



	if (tech->GetSSAO()->OnGeometryPass())
	{


		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera(),
			view->getViewMatrix());


	}
	else if (tech->GetShadow()->OnShadowPass())
	{

		tech->GetShadow()->UniformMVP(tech->GetShadow()->GetDirectionalShadow(env, info, view));


	}
	else
	{


		Space(glm::mat4(1.0), view);


	}


	terra->Render(ctrl->GetCameraPointer()->GetFrustum(), false);




}



void TerrainWrapper::Clean()
{


	TerrainShader::Clean();


	if (terra)
		delete terra;



}


