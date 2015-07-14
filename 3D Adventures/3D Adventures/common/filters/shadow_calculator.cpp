#include "shadow_calculator.hpp"





void ShadowBBox::Create(glm::mat4 VP, glm::vec3 dir, GLfloat far)
{



	glm::vec3 points[8];
	glm::vec3 centroid = glm::vec3(0, 0, 0);


	points[0] = glm::vec3(-1.0f, -1.0f, -1.0f); //xyz
	points[1] = glm::vec3(-1.0f, -1.0f, 1.0f);  //xyZ
	points[2] = glm::vec3(-1.0f, 1.0f, -1.0f);  //xYz
	points[3] = glm::vec3(1.0f, -1.0f, -1.0f);  //Xyz
	points[4] = glm::vec3(1.0f, 1.0f, -1.0f);   //XYz
	points[5] = glm::vec3(1.0f, -1.0f, 1.0f);   //XyZ
	points[6] = glm::vec3(-1.0f, 1.0f, 1.0f);   //xYZ
	points[7] = glm::vec3(1.0f, 1.0f, 1.0f);    //XYZ



	for (GLuint i = 0; i < 8; i++){


		points[i] = glm::vec3(glm::inverse(VP) * glm::vec4(points[i], 1.0f));
		centroid += points[i];

	}


	centroid /= 8;
	glm::vec3 temp_light_pos = centroid - dir * far;
	glm::mat4 ViewMatrix = glm::lookAt<GLfloat>(temp_light_pos, centroid, glm::vec3(0, 1, 0));


	GLfloat min_x, min_y, min_z, max_x, max_y, max_z;
	points[0] = glm::vec3(ViewMatrix * glm::vec4(points[0], 1.0f));


	min_x = max_x = points[0].x;
	min_y = max_y = points[0].y;
	min_z = max_z = points[0].z;


	for (GLuint i = 1; i < 8; i++)
	{




		points[i] = glm::vec3(ViewMatrix * glm::vec4(points[i], 1.0f));



		if (points[i].x < min_x)
			min_x = points[i].x;


		if (points[i].x > max_x)
			max_x = points[i].x;



		if (points[i].y < min_y)
			min_y = points[i].y;


		if (points[i].y > max_y)
			max_y = points[i].y;




		if (points[i].z < min_z)
			min_z = points[i].z;


		if (points[i].z > max_z)
			max_z = points[i].z;



	}



	glm::mat4 OrthoMatrix = glm::ortho<GLfloat>(min_x, max_x, min_y, max_y, max_z, min_z);
	this->LightMatrix = OrthoMatrix*ViewMatrix;



}







