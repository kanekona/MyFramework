#include "SoundTestEntity.h"
#include "Input\Input.h"
SoundTestEntity::SoundTestEntity()
{
	tag = "SoundTestEntity";
	angle = 0.0f;
}
SoundTestEntity::~SoundTestEntity()
{

}
void SoundTestEntity::Enter()
{
	sound.Create("./data/not/bgm/4.wav");
	sound.Play();
	sound.source->SetSourceRelative(true);
	sound.source->SetConeOuterGain(1.0f);
}
void SoundTestEntity::Update()
{
	ChangePosition();
	//ChangeDirection();
	ChangeVelocity();
	Rotation();
	DebugCout();
}
void SoundTestEntity::ChangePosition()
{
	Vec3 pos = sound.source->GetPosition();
	pos.x += Input::Get()->axis(In::AXIS_LEFT_X);
	pos.y += Input::Get()->axis(In::AXIS_LEFT_Y);
	if (Input::Get()->down(In::L1))
	{
		pos.z -= 1.0f;
	}
	else if (Input::Get()->down(In::R1))
	{
		pos.z += 1.0f;
	}
	sound.source->SetPosition(pos);
}
void SoundTestEntity::ChangeDirection()
{
	Vec3 pos = sound.source->GetDirection();
	pos.x += Input::Get()->axis(In::AXIS_LEFT_X);
	pos.y += Input::Get()->axis(In::AXIS_LEFT_Y);
	if (Input::Get()->down(In::L1))
	{
		pos.z -= 1.0f;
	}
	else if (Input::Get()->down(In::R1))
	{
		pos.z += 1.0f;
	}
	sound.source->SetDirection(pos);
}
void SoundTestEntity::ChangeVelocity()
{
	Vec3 vel = sound.source->GetVelocity();
	vel.x += Input::Get()->axis(In::AXIS_RIGHT_X);
	vel.y += Input::Get()->axis(In::AXIS_RIGHT_Y);
	vel.z -= Input::Get()->axis(In::AXIS_L2);
	vel.z += Input::Get()->axis(In::AXIS_R2);
	sound.source->SetVelocity(vel);
}
void SoundTestEntity::Rotation()
{
	angle += 1.0f;
	sound.source->SetConeOuterAngle((int)angle % 360);
	sound.source->SetConeInnerAngle((int)angle % 360);
}
void SoundTestEntity::DebugCout()
{
	system("cls");
	std::cout << "Sound.BufferID          = " << sound.source->GetBufferID() << std::endl;
	std::cout << "Sound.SourceRelative    = " << sound.source->GetSourceRelative() << std::endl;
	std::cout << "Sound.IsPlay            = " << sound.source->IsPlay() << std::endl;
	std::cout << "Sound.Looping           = " << sound.source->GetLoop() << std::endl;
	std::cout << "Sound.CurrentTime       = " << sound.source->GetTime() << std::endl;
	std::cout << "Sound.GetTime           = " << sound.buffer->GetTime() << std::endl;
	std::cout << "Sound.Volume            = " << sound.source->GetVolume() << std::endl;
	std::cout << "Sound.Processed         = " << sound.source->GetProcessed() << std::endl;
	std::cout << "Sound.Queued            = " << sound.source->GetQueued() << std::endl;
	std::cout << "Sound.Pitch             = " << sound.source->GetPitch() << std::endl;
	std::cout << "Sound.SourceType        = " << sound.source->GetSourceType() << std::endl;
	std::cout << "Sound.ReferenceDistance = " << sound.source->GetReferenceDistance() << std::endl;
	std::cout << "Sound.RolloffFactor     = " << sound.source->GetRolloffFactor() << std::endl;
	std::cout << "Sound.Position          = "; KL::cout(sound.source->GetPosition()); std::cout << std::endl;
	std::cout << "Sound.Velocity          = "; KL::cout(sound.source->GetVelocity()); std::cout << std::endl;
	std::cout << "Sound.Direction         = "; KL::cout(sound.source->GetDirection()); std::cout << std::endl;
	std::cout << "Sound.CoreInnerAngle    = " << sound.source->GetConeInnerAngle() << std::endl;
	std::cout << "Sound.CoreOuterAngle    = " << sound.source->GetConeOuterAngle() << std::endl;
	std::cout << "Sound.CoreOuterGain     = " << sound.source->GetConeOuterGain() << std::endl;
	/*float* orientation = sound.source->GetOrientation();
	std::cout << "Sound.Orientation       = " << orientation[0] << ":" << orientation[1] << ":" << orientation[2] << ":" << orientation[3] << ":" << orientation[4] << ":" << orientation[5] << std::endl;*/
}