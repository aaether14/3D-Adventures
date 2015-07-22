#include "transform_info.hpp"





void TransformInfo::Render(ViewInfo * info, View * view,
	ResourceLoader * res, Techniques * tech,
	MeshShader *shader, Entity*entity)
{


		entity->Render(info, view, res, tech, shader, matrix);

}



void TransformInfo::Clean()
{




}






