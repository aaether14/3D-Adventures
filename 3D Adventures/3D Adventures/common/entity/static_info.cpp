#include "static_info.hpp"



void StaticEntity::Render(Controller*ctrl, MeshShader *shader, glm::mat4 matrix)
{



	View * view = ctrl->GetCameraPointer()->GetView();
	ViewInfo * info = ctrl->GetCameraPointer()->GetInfo();
	Techniques * tech = ctrl->GetGameObject()->GetTechniques();
	Environment * env = ctrl->GetGameObject()->GetSettings()->GetEnv();



	if (tech->GetSSAO()->OnGeometryPass())
	{


		tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * matrix,
			view->getViewMatrix() * matrix);


	}
	else if (tech->GetShadow()->OnShadowPass())
	{


		tech->GetShadow()->UniformMVP(
			tech->GetShadow()->GetDirectionalShadow(env, info)
			*matrix);


	}
	else
	{


		shader->Space(matrix, view);



		glm::mat4 biasMatrix(
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0
			);




		shader->Set("LightMatrix", biasMatrix*
			tech->GetShadow()->GetDirectionalShadow(env, info)*matrix);

	}


	if (this->type == GRANNY_MODEL)
		this->gr_model->Render(-1);
	else if (this->type == AAETHER_MODEL)
		this->aa_model->Render();





}


void StaticEntityInfo::Render(Controller*ctrl, MeshShader *shader, StaticEntity ** entity)
{


	if (this->id >= 30)
	{


		if (this->id < 33)glDisable(GL_CULL_FACE);
		entity[this->id]->Render(ctrl, shader, this->matrix);
		if (this->id < 33)glEnable(GL_CULL_FACE);



	}
	else
	{
		entity[this->id]->Render(ctrl, shader, this->matrix);
	}


}





void StaticEntity::Clean()
{



	if (gr_model)
		delete gr_model;

	if (aa_model)
		delete aa_model;


}





