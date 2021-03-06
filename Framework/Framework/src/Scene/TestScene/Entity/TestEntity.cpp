#include "TestEntity.h"
#include "MovieImage\Video.h"
#include "File\File.hpp"
#include "Audio\StreamingSound.h"
#include "Input\Input.h"
#include "MovieImage\Images.h"
TestEntity::TestEntity()
{
	tag = "TestEntity";
}
TestEntity::~TestEntity()
{

}
void TestEntity::Entry()
{
	CVideo* movie = new CVideo;
	movie->Load("./data/not/videos/FrameworkTest", CMovieFormat::MP4, CMovieFormat::WAV);
	/*Images* movie = new Images;
	movie->Load("./data/not/videos/FrameworkTest", MovieFormat::MP4);*/
	SetChildren(movie);
}
void TestEntity::Update()
{
	CVideo* movie = static_cast<CVideo*>(GetChild<CVideo>());
	if (CInput::Get()->key->down(In::UP))
	{
		movie->SetSpeed(movie->GetSpeed() * 2);
	}
	else if (CInput::Get()->key->down(In::DOWN))
	{
		movie->SetSpeed(movie->GetSpeed() / 2);
	}
	else if (CInput::Get()->key->down(In::LEFT))
	{
		movie->SetTime(movie->GetTime() - 10);
	}
	else if (CInput::Get()->key->down(In::RIGHT))
	{
		movie->SetTime(movie->GetTime() + 10);
	}

	/*Images* movie = GetChild<Images>();
	if (Input::Get()->key->down(In::UP))
	{
		movie->SetSpeed(movie->GetSpeed() * 2);
	}
	else if (Input::Get()->key->down(In::DOWN))
	{
		movie->SetSpeed(movie->GetSpeed() / 2);
	}
	else if (Input::Get()->key->down(In::LEFT))
	{
		movie->SetTime(movie->GetTime() - 10);
	}
	else if (Input::Get()->key->down(In::RIGHT))
	{
		movie->SetTime(movie->GetTime() + 10);
	}
	std::cout << movie->GetTime() << ":" << movie->GetSpeed() << std::endl;*/
}