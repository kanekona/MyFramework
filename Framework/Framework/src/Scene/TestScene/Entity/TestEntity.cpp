#include "TestEntity.h"
#include "MovieImage\MovieImage.h"
#include "File\File.hpp"
TestEntity::TestEntity()
{
	tag = "TestEntity";
}
TestEntity::~TestEntity()
{

}
void TestEntity::Enter()
{
	MovieImage* movie = new MovieImage;
	movie->Load("./data/not/videos/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
	//movie->texture->SetShader(nullptr);
	SetChildren(movie);
	int count;
	std::string* str = KL::SplitString("abc def fhi  k", ' ', &count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << i << ":" << str[i] << std::endl;
	}
	delete[] str;
}
void TestEntity::Update()
{

}