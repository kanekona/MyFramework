#include "SoundTestEntity.h"
#include "Input\Input.h"
SoundTestEntity::SoundTestEntity()
{
	tag = "SoundTestEntity";
	angle = 0.0f;
	Source::SetListenerPosition(Vec3());
	Source::SetListenerGain(1.0f);
	float ListenOri[6] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };
	Source::SetOrientation(ListenOri);
}
SoundTestEntity::~SoundTestEntity()
{

}
void SoundTestEntity::Enter()
{
	//sound.Create("./data/not/bgm/4.wav");
	sound.Create("./data/not/bgm/mezamashi_kriitan.wav", true);
#if ENGINE_DEBUG
	sound.Test();
#endif ENGINE_DEBUG
	sound.Play();
	Vec2 vec2;
	Vec2Int veci2;
	vec2 = veci2;
	//sound.GetSource()->SetSourceRelative(true);
	//sound.GetSource()->SetConeOuterGain(1.0f);
}
void SoundTestEntity::Update()
{
	ChangePosition();
	//ChangeDirection();
	//ChangeVelocity();
	//Rotation();
	//UpdateReferenceDistance();
	DebugCout();
}
void SoundTestEntity::ChangePosition()
{
	/*Vec3 pos = sound.GetSource()->GetPosition();
	pos.x += Input::Get()->axis(In::AXIS_LEFT_X);
	pos.y += Input::Get()->axis(In::AXIS_LEFT_Y);
	if (Input::Get()->down(In::L1))
	{
		pos.z -= 1.0f;
	}
	else if (Input::Get()->down(In::R1))
	{
		pos.z += 1.0f;
	}*/
	Vec3 pos;
	angle += 0.2f;
	pos.x = cosf(angle);
	pos.z = sinf(angle);
	sound.GetSource()->SetPosition(pos);
}
void SoundTestEntity::ChangeDirection()
{
	Vec3 pos = sound.GetSource()->GetDirection();
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
	sound.GetSource()->SetDirection(pos);
}
void SoundTestEntity::ChangeVelocity()
{
	Vec3 vel = sound.GetSource()->GetVelocity();
	vel.x += Input::Get()->axis(In::AXIS_RIGHT_X);
	vel.y += Input::Get()->axis(In::AXIS_RIGHT_Y);
	vel.z -= Input::Get()->axis(In::AXIS_L2);
	vel.z += Input::Get()->axis(In::AXIS_R2);
	sound.GetSource()->SetVelocity(vel);
}
void SoundTestEntity::Rotation()
{
	angle += 1.0f;
	sound.GetSource()->SetConeOuterAngle((int)angle % 360);
	sound.GetSource()->SetConeInnerAngle((int)angle % 360);
}
void SoundTestEntity::UpdateReferenceDistance()
{
	sound.GetSource()->SetReferenceDistance(sound.GetSource()->GetReferenceDistance() + 1.0f);
}
void SoundTestEntity::DebugCout()
{
#if DEBUG
	system("cls");
	std::cout << "Sound.BufferID          = " << sound.GetSource()->GetBufferID() << std::endl;
	std::cout << "Sound.SourceRelative    = " << sound.GetSource()->GetSourceRelative() << std::endl;
	std::cout << "Sound.IsPlay            = " << sound.GetSource()->IsPlay() << std::endl;
	std::cout << "Sound.Looping           = " << sound.GetSource()->GetLoop() << std::endl;
	std::cout << "Sound.CurrentTime       = " << sound.GetSource()->GetTime() << std::endl;
	std::cout << "Sound.GetTime           = " << sound.GetBuffer()->GetTime() << std::endl;
	std::cout << "Sound.Volume            = " << sound.GetSource()->GetVolume() << std::endl;
	std::cout << "Sound.Processed         = " << sound.GetSource()->GetProcessed() << std::endl;
	std::cout << "Sound.Queued            = " << sound.GetSource()->GetQueued() << std::endl;
	std::cout << "Sound.Pitch             = " << sound.GetSource()->GetPitch() << std::endl;
	std::cout << "Sound.SourceType        = " << sound.GetSource()->GetSourceType() << std::endl;
	std::cout << "Sound.ReferenceDistance = " << sound.GetSource()->GetReferenceDistance() << std::endl;
	std::cout << "Sound.RolloffFactor     = " << sound.GetSource()->GetRolloffFactor() << std::endl;
	std::cout << "Sound.Position          = "; KL::cout(sound.GetSource()->GetPosition()); std::cout << std::endl;
	std::cout << "Sound.Velocity          = "; KL::cout(sound.GetSource()->GetVelocity()); std::cout << std::endl;
	std::cout << "Sound.Direction         = "; KL::cout(sound.GetSource()->GetDirection()); std::cout << std::endl;
	std::cout << "Sound.CoreInnerAngle    = " << sound.GetSource()->GetConeInnerAngle() << std::endl;
	std::cout << "Sound.CoreOuterAngle    = " << sound.GetSource()->GetConeOuterAngle() << std::endl;
	std::cout << "Sound.CoreOuterGain     = " << sound.GetSource()->GetConeOuterGain() << std::endl;
	std::cout << "Sound.Waveform          = " << +sound.GetBuffer()->GetWaveform(sound.GetSource()->GetTime()) << std::endl;
	/*float* orientation = sound.source->GetOrientation();
	std::cout << "Sound.Orientation       = " << orientation[0] << ":" << orientation[1] << ":" << orientation[2] << ":" << orientation[3] << ":" << orientation[4] << ":" << orientation[5] << std::endl;*/
#endif 
}