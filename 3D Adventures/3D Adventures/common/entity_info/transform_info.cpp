#include "transform_info.hpp"





void TransformInfo::Render(ViewInfo * info, View * view,
	ResourceLoader * res, Techniques * tech,
	MeshShader *shader, std::vector<Entity*>entities)
{


		entities[id]->Render(info, view, res, tech, shader, matrix);

}






