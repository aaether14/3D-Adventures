#include "filter_settings.hpp"




void FilterSettings::Reset()
{



	//SSAO

	SSAO.Enabled = false;
	SSAO.Radius = 1.5;
	SSAO.Power = 1.25;
	SSAO.NumSamples = 16;

	//Dof

	DoF.Enabled = false;



	//HDR


	//Bloom


	this->HDR.Bloom.Enabled = false;
	this->HDR.Bloom.Whitepoint = 1.0;



	//FXAA


	this->FXAA.Enabled = false;
	this->FXAA.span_max = 8.0;
	this->FXAA.reduce_min = 0.0078125;
	this->FXAA.reduce_mul = 0.125;



	SetShouldReset(false);




}


void FilterSettings::Init(char * path)
{

	SetPath(path);
	Reset();


}





void FilterSettings::Clean()
{






}





void FilterSettings::Save()
{


	std::ofstream fout(GetPath(), std::ios::binary);
	AFile::WriteToFile(fout, SSAO.Enabled);
	AFile::WriteToFile(fout, SSAO.NumSamples);
	AFile::WriteToFile(fout, SSAO.Power);
	AFile::WriteToFile(fout, SSAO.Radius);
	AFile::WriteToFile(fout, DoF.Enabled);
	AFile::WriteToFile(fout, HDR.Bloom.Enabled);
	AFile::WriteToFile(fout, HDR.Bloom.Whitepoint);
	AFile::WriteToFile(fout, FXAA.Enabled);
	AFile::WriteToFile(fout, FXAA.reduce_min);
	AFile::WriteToFile(fout, FXAA.reduce_mul);
	AFile::WriteToFile(fout, FXAA.span_max);
	fout.close();



}




void FilterSettings::Load()
{


	std::ifstream fin(GetPath(), std::ios::binary);
	AFile::ReadFromFile(fin, SSAO.Enabled);
	AFile::ReadFromFile(fin, SSAO.NumSamples);
	AFile::ReadFromFile(fin, SSAO.Power);
	AFile::ReadFromFile(fin, SSAO.Radius);
	AFile::ReadFromFile(fin, DoF.Enabled);
	AFile::ReadFromFile(fin, HDR.Bloom.Enabled);
	AFile::ReadFromFile(fin, HDR.Bloom.Whitepoint);
	AFile::ReadFromFile(fin, FXAA.Enabled);
	AFile::ReadFromFile(fin, FXAA.reduce_min);
	AFile::ReadFromFile(fin, FXAA.reduce_mul);
	AFile::ReadFromFile(fin, FXAA.span_max);
	fin.close();


	SetShouldReset(true);


}