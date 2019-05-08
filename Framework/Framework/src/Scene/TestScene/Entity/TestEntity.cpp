#include "TestEntity.h"
#include "MovieImage\MovieImage.h"
#include "File\File.hpp"
#include "Audio\StreamingSound.h"
#include "MovieImage\MediaPlayer.h"
TestEntity::TestEntity()
{
	tag = "TestEntity";
}
TestEntity::~TestEntity()
{

}
void TestEntity::Enter()
{
	//MovieImage* movie = new MovieImage;
	//movie->Load("./data/not/videos/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
	////movie->texture->SetShader(nullptr);
	//SetChildren(movie);
}
void TestEntity::Update()
{

}