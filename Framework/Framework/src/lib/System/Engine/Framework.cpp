#include "Framework.h"
#include "Data.h"
#include "Scene\SceneManager.h"
#include "Window\Window.h"
Framework::Framework(bool* destroy)
{
	sceneManager = nullptr;
	enableEngineDestroy = destroy;
	//Windowê∂ê¨
	window = new Window();
	time.Start();
	preTime = 0.0f;
	deltaTime = 0.0f;
}
Framework::~Framework()
{
	enableEngineDestroy = nullptr;
	delete sceneManager;
	delete window;
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
	sceneManager->ChangeScene(next);
}
Scene* Framework::GetScene()
{
	return sceneManager->Get();
}
void Framework::Update()
{
	deltaTime = time.GetTime() - preTime;
	preTime = time.GetTime();
	sceneManager->SceneUpdate();
}
Window* Framework::GetWindow()
{
	return window;
}
void Framework::EngineDestroy()
{
	*enableEngineDestroy = false;
}
void Framework::CreateSceneManager(Scene* begin)
{
	if (sceneManager == nullptr)
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
void Framework::GetSize(float* out)
{
	out[0] = (float)window->GetSize().x;
	out[1] = (float)window->GetSize().y;
}
float Framework::DeltaTime() const
{
	return deltaTime;
}
Framework* Framework::instance = nullptr;