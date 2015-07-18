#include "entity.hpp"





void Entity::Render(ViewInfo * info, View * view,
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




	ModelComponent * model_component = static_cast<ModelComponent*>(GetComponent("ModelComponent"));
	model_component->GetModel()->Render();





}



 


void Entity::Clean()
{





}


