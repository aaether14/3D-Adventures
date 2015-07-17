#include "static_info.hpp"



void StaticEntity::Render(ViewInfo * info, View * view,
	ResourceLoader * res, Techniques * tech,
	MeshShader *shader, glm::mat4 matrix)
{



	Environment * env = static_cast<Environment*>(res->Get("Environment"));



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



	for (GLuint i = 0; i < model_components.size(); i++)
		model_components[i]->Render();





}


void StaticEntityInfo::Render(ViewInfo * info, View * view,
	ResourceLoader * res, Techniques * tech,
	MeshShader *shader, std::vector<StaticEntity*>entities)
{


	if (this->id >= 30)
	{


		if (this->id < 33)glDisable(GL_CULL_FACE);
		entities[this->id]->Render(info, view, res, tech, shader, this->matrix);
		if (this->id < 33)glEnable(GL_CULL_FACE);



	}
	else
	{
		entities[this->id]->Render(info, view, res, tech, shader, this->matrix);
	}


}





void StaticEntity::Clean()
{



	for (GLuint i = 0; i < model_components.size(); i++)
		model_components[i]->Clean();

	model_components.clear();


}





