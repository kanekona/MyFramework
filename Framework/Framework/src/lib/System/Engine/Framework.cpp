#include "Framework.h"
#include "Data.h"
Framework::Framework(bool* destroy)
{
	this->sceneManager = nullptr;
	this->enableEngineDestroy = destroy;
	//Window¶¬
	this->window = new Window();
	time.Start();
	preTime = 0.0f;
	deltaTime = 0.0f;
}
Framework::~Framework()
{
	this->enableEngineDestroy = nullptr;
	delete this->sceneManager;
	delete this->window;
}
Framework* Framework::Create(bool* destroy)
{
	if (Framework::instance == nullptr)
	{
		Framework::instance = new Framework(destroy);
	}
	return Framework::Get();
}
Framework* Framework::Get()
{
	return Framework::instance;
}
void Framework::Destroy()
{
	//OG::Destroy<Framework>(instance);
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
void Framework::ChangeScene(Scene* next)
{
	this->sceneManager->ChangeScene(next);
}
Scene* Framework::GetScene()
{
	return this->sceneManager->Get();
}
void Framework::Update()
{
	deltaTime = time.GetTime() - preTime;
	preTime = time.GetTime();
	this->sceneManager->SceneUpdate();
}
Window* Framework::GetWindow()
{
	return this->window;
}
void Framework::EngineDestroy()
{
	*this->enableEngineDestroy = false;
}
void Framework::CreateSceneManager(Scene* begin)
{
	if (this->sceneManager == nullptr)
	{
		sceneManager = new SceneManager(begin);
	}
}
Vec2Int Framework::GetPosition(const unsigned int x, const unsigned int y, const unsigned int number)
{
	Vec2Int position(window->GetSize());
	position.x /= x;
	position.y /= y;
	position.x *= number % x;
	position.y *= number / x;
	return position;
}
Vec2Int Framework::GetSize(const unsigned int x, const unsigned int y)
{
	Vec2Int size(window->GetSize());
	size.x /= x;
	size.y /= y;
	return size;
}
float* Framework::GetSize()
{
	float size[] = { window->GetSize().x,window->GetSize().y };
	return size;
}
float Framework::DeltaTime() const
{
	return deltaTime;
}
Framework* Framework::instance = nullptr;