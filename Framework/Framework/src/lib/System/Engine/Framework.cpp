#include "Framework.h"
#include "Data.h"
#include "Scene\SceneManager.h"
#include "Window\Window.h"
CFramework::CFramework(bool* destroy)
{
	sceneManager = nullptr;
	enableEngineDestroy = destroy;
	//Windowê∂ê¨
	window = new CWindow();
	time.Start();
	preTime = 0.0f;
	deltaTime = 0.0f;
}
CFramework::~CFramework()
{
	enableEngineDestroy = nullptr;
	delete sceneManager;
	delete window;
}
CFramework* CFramework::Create(bool* destroy)
{
	if (CFramework::instance == nullptr)
	{
		CFramework::instance = new CFramework(destroy);
	}
	return CFramework::Get();
}
CFramework* CFramework::Get()
{
	return CFramework::instance;
}
void CFramework::Destroy()
{
	//OG::Destroy<Framework>(instance);
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
void CFramework::ChangeScene(CScene* next)
{
	sceneManager->ChangeScene(next);
}
CScene* CFramework::GetScene()
{
	return instance->sceneManager->Get();
}
void CFramework::Update()
{
	deltaTime = time.GetTime() - preTime;
	preTime = time.GetTime();
	sceneManager->SceneUpdate();
}
CWindow* CFramework::GetWindow()
{
	return instance->window;
}
void CFramework::EngineDestroy()
{
	*enableEngineDestroy = false;
}
void CFramework::CreateSceneManager(CScene* begin)
{
	if (sceneManager == nullptr)
	{
		sceneManager = new CSceneManager(begin);
	}
}
CVec2Int CFramework::GetPosition(const unsigned int x, const unsigned int y, const unsigned int number)
{
	CVec2Int position(window->GetSize());
	position.x /= x;
	position.y /= y;
	position.x *= number % x;
	position.y *= number / x;
	return position;
}
CVec2Int CFramework::GetSize(const unsigned int x, const unsigned int y)
{
	CVec2Int size(window->GetSize());
	size.x /= x;
	size.y /= y;
	return size;
}
void CFramework::GetSize(float* out)
{
	out[0] = (float)window->GetSize().x;
	out[1] = (float)window->GetSize().y;
}
float CFramework::DeltaTime() const
{
	return deltaTime;
}
CFramework* CFramework::instance = nullptr;