#include "TestScene.h"
#include "Entity\TestEntity.h"
#include "Entity\SoundTestEntity.h"
#include "Entity\InputTest.h"
#include "Entity\TextureTest.h"
#include "Entity\GraphTest.h"
#include "Entity\DelegateTest.h"
TestScene::TestScene()
{
	tag = "TestScene";
}
TestScene::~TestScene()
{

}
void TestScene::Entry()
{
#if ENGINE_DEVELOP
	//SetEntity(new SoundTestEntity());
	//SetEntity(new TestEntity());
	//SetEntity(new InputTest());
	SetEntity(new TextureTestEntity());
	SetEntity(new GraphTest());
	SetEntity(new DelegateTest());
#endif
}