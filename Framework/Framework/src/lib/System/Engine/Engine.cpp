#include "Engine.h"
#include "Input\Input.h"
#include "Random\Random.h"
#include "Event\Event.h"
#include "ResourceManager\ResourceManager.h"
#include "Audio\Audio.h"
#include "StrID\StrID.h"
#include "Initializer.h"
#include "Framework.h"
#include "Scene\Scene.h"
CEngine::CEngine()
{
	//OpenGL,OpenFW Initialize
	GLFWInitialize();
	//Create Engine Initializer
	initializer = new CInitializer();
	//GameFrameworkの生成
	enable = true;
	framework = CFramework::Create(&enable);
	//Get Framework Window Address
	window = framework->GetWindow();
	//Window Create
	window->Create(initializer->ConfigWindow());
	//Window Config
	window->Limits();
	window->InMouseMode(true);
	window->SetIcon("./data/image/testicon.png");
	//Scene Create
	framework->CreateSceneManager(initializer->SceneAdaptation());
	//OutsideLibrary Initialize
	OutsideLibraryInitialize();
	//AudioDeviceの設定
	audiodevice = new CAudio();
	//ResourceManagetの生成
	CResourceManager::Create();
	//Inputの生成
	CInput::Create(framework->GetWindow()->GetFWWindow());
	//Delete Engine Initializer
	delete initializer;
	CEventTask ev;
	ev.Load(EEvent::RESOURCE_LOAD, "./data/event/sampleLoad.og");
	//Scene Start
	framework->GetScene()->Entry();
}
CEngine::~CEngine()
{
	//Delete Input
	CInput::Destroy();
	//Delete ResourceManager
	CResourceManager::Destroy();
	//Delete AudioDevice
	delete audiodevice;
	//Delete GameFramework
	CFramework::Destroy();
	//End GLFW
	glfwTerminate();
}
void CEngine::GLFWInitialize()
{
	//GLFW Initialize
	if (!glfwInit())
	{
		throw ERROR_GLFE_INIT;
	}
}
void CEngine::OutsideLibraryInitialize()
{
	//OpenGL Version
	//多分Windowより前に宣言すると描画がされない
	//必要かよくわからん
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//User Window
	glfwMakeContextCurrent(window->GetFWWindow());
	//Timeing Specification Double Buffer
	glfwSwapInterval(1);
#if defined(_MSC_VER)
	//GLEW Initialize
	if (glewInit() != GLEW_OK)
	{
		//Destroy Window and Cursor
		glfwTerminate();
		throw ERROR_GLEW_INIT;
	}
#endif
	//Rendering Range
	glViewport(0, 0, (GLsizei)window->GetSize().x, (GLsizei)window->GetSize().y);
	//Matrix Initialize
	glLoadIdentity();
	//ウインドウの座標の巻線に基づいてポリゴンをカリングする
//	glEnable(GL_CULL_FACE);
	//Specification Normal Vector
	glEnable(GL_NORMALIZE);
	//Back Color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Random Seed Initialize
	Random::Init();
}
bool CEngine::SystemUpdate()
{
	//Update Check
	if (fps.FrameCheck())
	{
		//Double Buffer
		glfwSwapBuffers(window->GetFWWindow());
		//Device Update
		glfwPollEvents();
		//Device Class Update
		CInput::Get()->Update();
		//Matrix Mode Change
		glMatrixMode(GL_MODELVIEW);
		//Clear Buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//FragmentColor to Color Buffer Brend
		glEnable(GL_BLEND);
		//Calculation Pixel
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Framework Update
		framework->Update();
		//Delete Check
		if (!enable)
		{
			glfwDestroyWindow(window->GetFWWindow());
			return false;
		}
	}
	return !glfwWindowShouldClose(window->GetFWWindow());
}