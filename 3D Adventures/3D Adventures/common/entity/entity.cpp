#include "entity.hpp"





void Entity::Render(ViewInfo * info, View * view,
	ResourceLoader * res, Techniques * tech,
	MeshShader *shader, glm::mat4 matrix)
{



	ModelComponent * model_component = static_cast<ModelComponent*>(GetComponent("ModelComponent"));



	if (model_component)
	{


		Environment * env = static_cast<Environment*>(res->Get("Environment"));
		InfoComponent * info_component = static_cast<InfoComponent*>(GetComponent("InfoComponent"));


		if (tech->GetSSAO()->OnGeometryPass())
			tech->GetSSAO()->SetGeometryPassUniforms(view->getCamera() * matrix,
				view->getViewMatrix() * matrix);
		else if (tech->GetShadow()->OnShadowPass())
			tech->GetShadow()->UniformMVP(
				tech->GetShadow()->GetDirectionalShadow(env, info)
				*matrix);
		else
		{


			//Passing MVP


			shader->Space(matrix, view);


			glm::mat4 biasMatrix(
				0.5, 0.0, 0.0, 0.0,
				0.0, 0.5, 0.0, 0.0,
				0.0, 0.0, 0.5, 0.0,
				0.5, 0.5, 0.5, 1.0
				);



			//Also light MVP


			shader->Set("LightMatrix", biasMatrix*
				tech->GetShadow()->GetDirectionalShadow(env, info)*matrix);

		}




		if (!(tech->GetSSAO()->OnGeometryPass() && !info_component->GetInfo()->affected_by_ssao))
		{


			if (!info_component->GetInfo()->cull)
			{
				glDisable(GL_CULL_FACE);
				model_component->GetModel()->Render();
				glEnable(GL_CULL_FACE);
			}
			else
				model_component->GetModel()->Render();

		}



	}


}



 


void Entity::Clean()
{


	components.clear();


}


