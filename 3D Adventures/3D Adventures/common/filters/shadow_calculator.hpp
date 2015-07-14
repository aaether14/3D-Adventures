#ifndef SHADOW_CALCULATOR_HPP
#define SHADOW_CALCULATOR_HPP



#include <util/controller_math.hpp>


#define MAX_SPLITS 4


struct frustum
{
	float neard;
	float fard;
	float fov;
	float ratio;
	glm::vec3 point[8];
};


class ShadowBBox
{

	
	glm::mat4 LightMatrix;
	int cur_num_splits;
	float split_weight;

	///




public:


	inline void updateFrustumPoints(frustum *f, glm::vec3 &center, glm::vec3 &view_dir)
	{
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::cross(view_dir, up);

		glm::vec3 fc = center + view_dir*f->fard;
		glm::vec3 nc = center + view_dir*f->neard;

		right = glm::normalize(right);
		up = glm::normalize(glm::cross(right, view_dir));

		// these heights and widths are half the heights and widths of
		// the near and far plane rectangles
		float near_height = tan(f->fov / 2.0f) * f->neard;
		float near_width = near_height * f->ratio;
		float far_height = tan(f->fov / 2.0f) * f->fard;
		float far_width = far_height * f->ratio;

		f->point[0] = nc - up*near_height - right*near_width;
		f->point[1] = nc + up*near_height - right*near_width;
		f->point[2] = nc + up*near_height + right*near_width;
		f->point[3] = nc - up*near_height + right*near_width;

		f->point[4] = fc - up*far_height - right*far_width;
		f->point[5] = fc + up*far_height - right*far_width;
		f->point[6] = fc + up*far_height + right*far_width;
		f->point[7] = fc - up*far_height + right*far_width;
	}


	inline void updateSplitDist(frustum f[MAX_SPLITS], float nd, float fd)
	{
		float lambda = split_weight;
		float ratio = fd / nd;
		f[0].neard = nd;

		for (int i = 1; i<cur_num_splits; i++)
		{
			float si = i / (float)cur_num_splits;

			f[i].neard = lambda*(nd*powf(ratio, si)) + (1 - lambda)*(nd + (fd - nd)*si);
			f[i - 1].fard = f[i].neard * 1.005f;
		}
		f[cur_num_splits - 1].fard = fd;
	}


	frustum frustum_splits[MAX_SPLITS];

	void Create(glm::mat4 VP, glm::vec3 dir, GLfloat far);
	inline glm::mat4 GetLightMatrix(){return this->LightMatrix;}
	inline ShadowBBox()
	{
		this->cur_num_splits = 4; 
		this->split_weight = 0.75f;
		for (GLuint i = 0; i < MAX_SPLITS; i++)
		{
			this->frustum_splits[i].fov = 60.0;
			this->frustum_splits[i].ratio = GLfloat(4.0f) / GLfloat(3.0f);
		}
	}
	inline void print_splits()
	{
		for (GLuint i = 0; i < cur_num_splits; i++)
			printf("%4.2fN -- %4.2fF\n", this->frustum_splits[i].neard, this->frustum_splits[i].fard);
		printf("%\n");
	}
	inline void print_frustum(frustum f)
	{
		for (GLuint i = 0; i < 8; i++)
			printf("%4.2f\n", f.point[i]);
		printf("\n");
	}

};





#endif