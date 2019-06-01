#include "TestScene.h"
#include "Entity\TestEntity.h"
#include "Entity\SoundTestEntity.h"
TestScene::TestScene()
{
	tag = "TestScene";
}
TestScene::~TestScene()
{

}
void TestScene::Enter()
{
	SetEntity(new SoundTestEntity());
}