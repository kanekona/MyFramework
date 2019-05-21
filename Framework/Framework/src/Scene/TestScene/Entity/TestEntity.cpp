#include "TestEntity.h"
#include "MovieImage\Video.h"
#include "File\File.hpp"
#include "Audio\StreamingSound.h"
#include "Input\Input.h"
TestEntity::TestEntity()
{
	tag = "TestEntity";
}
TestEntity::~TestEntity()
{

}
void TestEntity::Enter()
{
	Video* movie = new Video;
	movie->Load("./data/not/videos/FrameworkTest", MovieFormat::MP4, MovieFormat::WAV);
	SetChildren(movie);
}
void TestEntity::Update()
{

}