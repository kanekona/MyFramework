#include "TestScene.h"
#include "Entity\TestEntity.h"
#include "Entity\SoundTestEntity.h"
#include "Entity\InputTest.h"
TestScene::TestScene()
{
	tag = "TestScene";
}
TestScene::~TestScene()
{

}
void TestScene::Enter()
{
#if ENGINE_DEVELOP
	//SetEntity(new SoundTestEntity());
	//SetEntity(new TestEntity());
	SetEntity(new InputTest());
#endif
}