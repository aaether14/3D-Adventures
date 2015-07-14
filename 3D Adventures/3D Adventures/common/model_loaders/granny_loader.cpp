#include "granny_loader.h"





void print_matrix(granny_matrix_4x4 m)
{


	printf("%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f,\n%1.2f, %1.2f, %1.2f, %1.2f\n\n",
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3]
		);



}


int GrannyModel::Init()
{


	if (!GrannyVersionsMatch)
	{
		printf("Warning: the Granny DLL currently loaded "
			"doesn't match the .h file used during compilation\n");
		return EXIT_FAILURE;
	}


	glGenVertexArrays(1, &m_VAO);
	return EXIT_SUCCESS;


}

int GrannyModel::Load(const char* path){


	GlobalScene.SceneFile = GrannyReadEntireFile(path);


	if (GlobalScene.SceneFile == NULL)
		return EXIT_FAILURE;


	GlobalScene.SceneFileInfo = GrannyGetFileInfo(GlobalScene.SceneFile);
	if (GlobalScene.SceneFileInfo == NULL)
		return EXIT_FAILURE;


	if (CreateDemoTextures() == false ||
		CreateDemoModels() == false ||
		CreateSharedPoses() == false)
	{
		return EXIT_FAILURE;
	}


	GrannyGetSystemSeconds(&GlobalStartClock);
	return EXIT_SUCCESS;


}

bool GrannyModel::CreateDemoTextures()
{



	assert(GlobalScene.SceneFileInfo);
	granny_file_info* Info = GlobalScene.SceneFileInfo;


	for (granny_int32x TexIdx = 0; TexIdx < Info->TextureCount; ++TexIdx)
	{


		granny_texture* GrannyTexture = Info->Textures[TexIdx];
		assert(GrannyTexture);

		DemoTexture* NewTex = new DemoTexture;
		NewTex->Name = new char[strlen(GrannyTexture->FromFileName) + 1];
		strcpy(NewTex->Name, GrannyTexture->FromFileName);


		string p(NewTex->Name);
		p = p.substr(p.find_last_of("\\") + 1, p.length());
		string FullPath = TEX_DIR + p;



		NewTex->TextureName = TextureObject::load_texture(AString::char_to_str(FullPath), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		GlobalScene.Textures.push_back(NewTex);




	}
	if (GlobalScene.SceneFile->SectionCount >= GrannyStandardTextureSection)
	{


		GrannyFreeFileSection(GlobalScene.SceneFile,
			GrannyStandardTextureSection);


	}

	return true;


}





DemoMesh* GrannyModel::CreateBoundMesh(granny_mesh* GrannyMesh,
	granny_model_instance* ModelInstance)
{



	assert(GrannyMesh);
	assert(ModelInstance);
	granny_model* SourceModel = GrannyGetSourceModel(ModelInstance);
	DemoMesh* NewMesh = new DemoMesh;


	NewMesh->Mesh = GrannyMesh;
	NewMesh->MeshBinding = GrannyNewMeshBinding(GrannyMesh,
		SourceModel->Skeleton,
		SourceModel->Skeleton);




	if (GrannyMeshIsRigid(NewMesh->Mesh))
	{



		GLint bufferSize = GrannyGetMeshVertexCount(NewMesh->Mesh) * sizeof(granny_pnt332_vertex);
		char* VertexBuffer = new char[bufferSize];

		GrannyCopyMeshVertices(NewMesh->Mesh,
			GrannyPNT332VertexType,
			VertexBuffer);

		glGenBuffers(1, &NewMesh->VertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, NewMesh->VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, VertexBuffer, GL_STATIC_DRAW);

		delete[] VertexBuffer;



	}
	else
	{


		GLint bufferSize = GrannyGetMeshVertexCount(NewMesh->Mesh) * sizeof(granny_pwnt3432_vertex);
		char* VertexBuffer = new char[bufferSize];

		GrannyCopyMeshVertices(NewMesh->Mesh,
			GrannyPWNT3432VertexType,
			VertexBuffer);

		glGenBuffers(1, &NewMesh->VertexBufferObject);
		glBindBuffer(GL_ARRAY_BUFFER, NewMesh->VertexBufferObject);
		glBufferData(GL_ARRAY_BUFFER, bufferSize, VertexBuffer, GL_STATIC_DRAW);

		delete[] VertexBuffer;



	}


	{


		GLint bufferSize = GrannyGetMeshIndexCount(NewMesh->Mesh) * sizeof(granny_int32);


		char* IndexBuffer = new char[bufferSize];
		GrannyCopyMeshIndices(NewMesh->Mesh, 4, IndexBuffer);



		glGenBuffers(1, &NewMesh->IndexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NewMesh->IndexBufferObject);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, IndexBuffer, GL_STATIC_DRAW);


		delete[] IndexBuffer;


	}



	for (granny_int32x MatIdx = 0; MatIdx < GrannyMesh->MaterialBindingCount; ++MatIdx)
	{



		granny_material* Material = GrannyMesh->MaterialBindings[MatIdx].Material;
		DemoTexture* Found = NULL;


		if (Material->MapCount >= 1)
		{
			for (granny_int32x MapIdx = 0; MapIdx < Material->MapCount; ++MapIdx)
			{
				granny_material_map& Map = Material->Maps[MapIdx];
				if (_stricmp(Map.Usage, "Diffuse Color") == 0 && Map.Material->Texture)
				{
					for (granny_uint32x i = 0; i < GlobalScene.Textures.size(); ++i)
					{
						if (_stricmp(Map.Material->Texture->FromFileName, GlobalScene.Textures[i]->Name) == 0)
						{
							Found = GlobalScene.Textures[i];
							break;
						}
					}
				}
			}
		}



		NewMesh->MaterialBindings.push_back(Found);


	}


	return NewMesh;



}



bool GrannyModel::CreateDemoModels()
{



	assert(GlobalScene.SceneFileInfo);
	granny_file_info* Info = GlobalScene.SceneFileInfo;


	for (granny_int32x ModelIdx = 0; ModelIdx < Info->ModelCount; ++ModelIdx)
	{


		granny_model* GrannyModel = Info->Models[ModelIdx];
		assert(GrannyModel);



		if (GrannyModel->MeshBindingCount > 0)
		{

			DemoModel* NewModel = new DemoModel;
			GlobalScene.Models.push_back(NewModel);


			NewModel->ModelInstance = GrannyInstantiateModel(GrannyModel);
			GrannyBuildCompositeTransform4x4(&GrannyModel->InitialPlacement,
				NewModel->InitialMatrix);

			for (granny_int32x MeshIdx = 0;
				MeshIdx < GrannyModel->MeshBindingCount;
				++MeshIdx)
			{


				granny_mesh* GrannyMesh = GrannyModel->MeshBindings[MeshIdx].Mesh;
				assert(GrannyMesh);

				DemoMesh* NewMesh = CreateBoundMesh(GrannyMesh, NewModel->ModelInstance);
				assert(NewMesh);
				NewModel->BoundMeshes.push_back(NewMesh);


			}


		}


	}

	return true;


}




void GrannyModel::AttachGrannyModel(GrannyModel*GrannyAttachModel, const char*bone_name)
{



	GrannyAttachModel->GlobalScene.Models[0]->AttachedTo = this->GlobalScene.Models[0];
	GrannyAttachModel->GlobalScene.Models[0]->AttachModelBone = 0;
	GrannyFindBoneByNameLowercase(GrannyGetSourceSkeleton(this->GlobalScene.Models[0]->ModelInstance),
		bone_name,
		&GrannyAttachModel->GlobalScene.Models[0]->BaseModelBone);



}




granny_animation* GrannyLoadAnimation(const char* path)
{


	granny_file * anim_file = GrannyReadEntireFile(path);
	if (anim_file == NULL)
		return NULL;
	granny_file_info* anim_info = GrannyGetFileInfo(anim_file);
	if (anim_info == NULL)
		return NULL;
	for (granny_int32x AnimIdx = 0; AnimIdx < anim_info->AnimationCount; ++AnimIdx)
	{
		granny_animation* Animation = anim_info->Animations[AnimIdx];

		return Animation;
	}



}



void GrannyModel::LoadAnimation(const char*path)
{



	granny_animation*animation = NULL;
	animation = GrannyLoadAnimation(path);
	granny_control*control = GrannyPlayControlledAnimation(0.0f, animation, GlobalScene.Models[0]->ModelInstance);
	this->GrannyControls.push_back(control);



}




void GrannyModel::PlayAnimation(GLuint index, GLuint loop_count)
{



	if (this->GrannyControls[index])
	{
		GrannySetControlLoopCount(this->GrannyControls[index], loop_count);
		GrannyFreeControlOnceUnused(this->GrannyControls[index]);
	}



}




bool GrannyModel::CreateSharedPoses()
{


	GlobalScene.MaxBoneCount = -1;




	for (granny_uint32x i = 0; i < GlobalScene.Models.size(); ++i)
	{


		granny_skeleton* Skeleton =
			GrannyGetSourceSkeleton(GlobalScene.Models[i]->ModelInstance);



		if (Skeleton->BoneCount > GlobalScene.MaxBoneCount)
			GlobalScene.MaxBoneCount = Skeleton->BoneCount;


	}



	if (GlobalScene.MaxBoneCount != -1)
	{
		GlobalScene.SharedLocalPose = GrannyNewLocalPose(GlobalScene.MaxBoneCount);
		GlobalScene.SharedWorldPose =
			GrannyNewWorldPoseNoComposite(GlobalScene.MaxBoneCount);

		return true;
	}



	else
		return false;


}





void GrannyModel::Update(granny_real32 const CurrentTime)
{



	for (size_t Idx = 0; Idx < GlobalScene.Models.size(); Idx++)
	{
		DemoModel* Model = GlobalScene.Models[Idx];
		GrannySetModelClock(Model->ModelInstance, CurrentTime);
	}



}





void GrannyModel::Render(GLuint anim_num)
{



	granny_real32 CurrentTime;
	{


		granny_system_clock CurrClock;
		GrannyGetSystemSeconds(&CurrClock);

		CurrentTime = GrannyGetSecondsElapsed(&GlobalStartClock, &CurrClock);

	}


	Update(CurrentTime);


	glBindVertexArray(m_VAO);


	for (size_t Idx = 0; Idx < GlobalScene.Models.size(); Idx++)
		RenderModel(GlobalScene.Models[Idx], anim_num);


	glBindVertexArray(0);



}




void GrannyModel::RenderMeshBindings(DemoModel* Model, granny_world_pose* Pose)
{



	for (size_t MeshIndex = 0; MeshIndex < Model->BoundMeshes.size(); ++MeshIndex)
	{


		DemoMesh* Mesh = Model->BoundMeshes[MeshIndex];
		int const *ToBoneIndices =
			GrannyGetMeshBindingToBoneIndices(Mesh->MeshBinding);



		if (GrannyMeshIsRigid(Mesh->Mesh))
		{



			glBindBuffer(GL_ARRAY_BUFFER, Mesh->VertexBufferObject);
			glEnableVertexAttribArray(POSITION_LOCATION);
			glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE,
				sizeof(granny_pnt332_vertex),
				Offset(granny_pnt332_vertex, Position[0]));
			glEnableVertexAttribArray(TEX_COORD_LOCATION);
			glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE,
				sizeof(granny_pnt332_vertex),
				Offset(granny_pnt332_vertex, UV[0]));
			glEnableVertexAttribArray(NORMAL_LOCATION);
			glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE,
				sizeof(granny_pnt332_vertex),
				Offset(granny_pnt332_vertex, Normal[0]));



		}
		else
		{




			int const NumMeshBones = GrannyGetMeshBindingBoneCount(Mesh->MeshBinding);
			assert(NumMeshBones <= MAX_BONES);
			GrannyBuildIndexedCompositeBuffer(
				GrannyGetMeshBindingToSkeleton(Mesh->MeshBinding),
				Pose,
				ToBoneIndices,
				NumMeshBones,
				CompositeBuffer);




			glBindBuffer(GL_ARRAY_BUFFER, Mesh->VertexBufferObject);
			glEnableVertexAttribArray(POSITION_LOCATION);
			glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE,
				sizeof(granny_pwnt3432_vertex),
				Offset(granny_pwnt3432_vertex, Position[0]));
			glEnableVertexAttribArray(TEX_COORD_LOCATION);
			glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE,
				sizeof(granny_pwnt3432_vertex),
				Offset(granny_pwnt3432_vertex, UV[0]));
			glEnableVertexAttribArray(NORMAL_LOCATION);
			glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE,
				sizeof(granny_pwnt3432_vertex),
				Offset(granny_pwnt3432_vertex, Normal[0]));
			glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
			glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_UNSIGNED_BYTE, GL_TRUE,
				sizeof(granny_pwnt3432_vertex),
				Offset(granny_pwnt3432_vertex, BoneWeights[0]));
			glEnableVertexAttribArray(BONE_ID_LOCATION);
			glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_UNSIGNED_BYTE,
				sizeof(granny_pwnt3432_vertex),
				Offset(granny_pwnt3432_vertex, BoneIndices[0]));



		}




		int GroupCount = GrannyGetMeshTriangleGroupCount(Mesh->Mesh);


		granny_tri_material_group *Group =
			GrannyGetMeshTriangleGroups(Mesh->Mesh);



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh->IndexBufferObject);
		while (GroupCount--)
		{
			GLuint texName = 0;
			if (Group->MaterialIndex < int(Mesh->MaterialBindings.size()) &&
				Mesh->MaterialBindings[Group->MaterialIndex] != NULL)
			{
				DemoTexture* Texture = Mesh->MaterialBindings[Group->MaterialIndex];
				texName = Texture->TextureName;
			}




			glBindTexture(GL_TEXTURE_2D, texName);


			glDrawElements(GL_TRIANGLES,
				Group->TriCount * 3,
				GL_UNSIGNED_INT,
				((char*)0) + (Group->TriFirst * 12));


			++Group;
			glBindTexture(GL_TEXTURE_2D, 0);


		}


	}


}

void GrannyModel::RenderAttachedModel(GrannyModel *AttachedGrannyModel)
{



	DemoModel * AttachedModel = AttachedGrannyModel->GlobalScene.Models[0];

	assert(AttachedModel && AttachedModel->AttachedTo);
	assert(AttachedModel->BaseModelBone != -1);
	assert(AttachedModel->AttachModelBone != -1);

	granny_skeleton* BaseSkeleton =
		GrannyGetSourceSkeleton(AttachedModel->AttachedTo->ModelInstance);
	assert(AttachedModel->BaseModelBone >= 0 &&
		AttachedModel->BaseModelBone < BaseSkeleton->BoneCount);

	GrannySampleModelAnimations(AttachedModel->AttachedTo->ModelInstance,
		0, BaseSkeleton->BoneCount,
		GlobalScene.SharedLocalPose);

	granny_matrix_4x4 BaseMatrix;
	GrannyGetWorldMatrixFromLocalPose(BaseSkeleton,
		AttachedModel->BaseModelBone,
		GlobalScene.SharedLocalPose,
		AttachedModel->AttachedTo->InitialMatrix,
		(granny_real32*)BaseMatrix,
		NULL, NULL);

	granny_skeleton* AttachSkeleton =
		GrannyGetSourceSkeleton(AttachedModel->ModelInstance);
	GrannySampleModelAnimations(AttachedModel->ModelInstance,
		0, AttachSkeleton->BoneCount,
		GlobalScene.SharedLocalPose);



	granny_matrix_4x4 AttachmentMatrix;
	GrannyGetAttachmentOffset(AttachSkeleton,
		AttachedModel->AttachModelBone,
		GlobalScene.SharedLocalPose,
		NULL,
		(granny_real32*)AttachmentMatrix,
		NULL, NULL);



	granny_matrix_4x4 Offset4x4;
	GrannyColumnMatrixMultiply4x3((granny_real32*)Offset4x4,
		(granny_real32*)AttachmentMatrix,
		(granny_real32*)BaseMatrix);



	memcpy(CompositeBuffer[128], Offset4x4, 16 * sizeof(granny_real32));



	glBindVertexArray(AttachedGrannyModel->m_VAO);
	RenderMeshBindings(AttachedModel, GlobalScene.SharedWorldPose);
	glBindVertexArray(0);


}



void GrannyModel::RenderModel(DemoModel* Model, GLuint anim_num)
{





	if (anim_num != -1)
		for (GLuint i = 0; i < GrannyControls.size(); i++)
			if (i == anim_num)
				GrannySetControlActive(GrannyControls[i], true);
			else
				GrannySetControlActive(GrannyControls[i], false);




	GrannySampleModelAnimationsAccelerated(
		Model->ModelInstance,
		GrannyGetSourceSkeleton(Model->ModelInstance)->BoneCount,
		Model->InitialMatrix,
		GlobalScene.SharedLocalPose,
		GlobalScene.SharedWorldPose);



	RenderMeshBindings(Model, GlobalScene.SharedWorldPose);

}


