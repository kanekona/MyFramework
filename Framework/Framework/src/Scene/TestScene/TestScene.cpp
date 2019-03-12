#include "TestScene.h"
#include "Entity\TestEntity.h"
TestScene::TestScene()
{
	tag = "TestScene";
}
TestScene::~TestScene()
{

}
void TestScene::Enter()
{
	SetEntity(new TestEntity());
}