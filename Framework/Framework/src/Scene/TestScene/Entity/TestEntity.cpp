#include "TestEntity.h"
#include "MovieImage\MovieImage.h"
TestEntity::TestEntity()
{
	tag = "TestEntity";
}
TestEntity::~TestEntity()
{

}
void TestEntity::Enter()
{
	MovieImage* movie = new MovieImage();
	movie->Load("./data/image/kiritan/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
	SetChildren(movie);
}
void TestEntity::Update()
{

}
