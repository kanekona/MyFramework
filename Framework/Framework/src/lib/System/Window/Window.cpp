#include "Window.h"
#include "stb_image.h"
#include "Scene\Scene.h"
#include "Engine\Framework.h"
CWindow::CWindow()
{
	//Default
	widht = 640;
	height = 480;
	enableFullScreen = false;
	name = "NoName";
	enableIcon = false;
	isVisualization = false;
	window = nullptr;
	position = CVec2Int(0, 30);
}
CWindow::CWindow(const int wi, const int he, const char* windowname, const bool screen,const CVec2Int& pos)
	:widht(wi)
	, height(he)
	, name(windowname)
	, enableFullScreen(screen)
	, position(pos)
{
	window = glfwCreateWindow(widht, height, name.c_str(), enableFullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	if (!window) {
		glfwTerminate();
		return;
	}
	glfwSetWindowPos(window, position.x, position.y);
}
CWindow::~CWindow()
{
	glfwSetWindowIcon(window, 0, NULL);
}

bool CWindow::Create(const int wi, const int he, char* windowname, const bool screen,const CVec2Int& pos)
{
	widht = wi;
	height = he;
	name = windowname;
	enableFullScreen = screen;
	position = pos;
	window = glfwCreateWindow(widht, height, name.c_str(), enableFullScreen ? glfwGetPrimaryMonitor() : NULL, window ? window : NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}
	glfwSetWindowPos(window, position.x, position.y);
	return true;
}
bool CWindow::Create()
{
	window = glfwCreateWindow(widht, height, name.c_str(), enableFullScreen ? glfwGetPrimaryMonitor() : NULL, window ? window : NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}
	glfwSetWindowPos(window, position.x, position.y);
	return true;
}
bool CWindow::Create(const CWindowParameter& parameter)
{
	widht = parameter.size.x;
	height = parameter.size.y;
	name = parameter.name;
	enableFullScreen = parameter.enableFullScreen;
	position = parameter.position;
	window = glfwCreateWindow(widht, height, name.c_str(), enableFullScreen ? glfwGetPrimaryMonitor() : NULL, window ? window : NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}
	glfwSetWindowPos(window, (int)position.x, (int)position.y);
	return true;
}
void CWindow::SetIcon(const std::string& path)
{
	//stbimage���g���ĉ摜��ǂݍ���
	image[0].pixels = stbi_load(path.c_str(), &image[0].width, &image[0].height, 0, 4);
	//glfw�ɐݒ肵����Window�ƃA�C�R���ɂ������摜�f�[�^�ƌ��𑗂�
	glfwSetWindowIcon(window, 1, image);
	//�f�[�^�̉��
	stbi_image_free(image[0].pixels);
}
void CWindow::Limits()
{
	//Window�̃T�C�Y���Œ艻������
	glfwSetWindowSizeLimits(window, widht, height, widht, height);
	//window�̃A�X�y�N�g����Œ肳����
	glfwSetWindowAspectRatio(window, 16, 9);
	//window�̃T�C�Y��ύX����(�Œ艻����Ă���ꍇ�ύX�͂ł��Ȃ�)
	//glfwSetWindowSize(window, 1920, 1080);
}
void CWindow::Limits(const int w,const int h)
{
	//Window�̃T�C�Y���Œ艻������
	glfwSetWindowSizeLimits(window, w, h, w, h);
	//window�̃A�X�y�N�g����Œ肳����
	glfwSetWindowAspectRatio(window, 16, 9);
	//window�̃T�C�Y��ύX����(�Œ艻����Ă���ꍇ�ύX�͂ł��Ȃ�)
	//glfwSetWindowSize(window, 1920, 1080);
}
void CWindow::Enable()
{
	if (enableIcon)
	{
		//Icon�����ꂽwindow�����ɖ߂�
		glfwRestoreWindow(window);
		enableIcon = false;
	}
	else
	{
		//window��Icon��������
		glfwIconifyWindow(window);
		enableIcon = true;
	}
}

void CWindow::Visualization()
{
	if (isVisualization)
	{
		//�B�ꂽwindow�����ɖ߂�
		glfwShowWindow(window);
		isVisualization = false;
	}
	else
	{
		//window���B��
		glfwHideWindow(window);
		isVisualization = true;
	}
}

void CWindow::InMouseMode(const bool index)
{
	glfwSetInputMode(window, GLFW_CURSOR, index ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}
CVec2Int CWindow::GetSize() const
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);
	return CVec2Int(w, h);
}
CVec2Int CWindow::GetPos() const
{
	int x, y;
	glfwGetWindowPos(window, &x, &y);
	return CVec2Int(x, y);
}
void CWindow::CreatePosition(const CVec2Int& pos)
{
	position = pos;
}
GLFWwindow* CWindow::GetFWWindow() const
{
	return window;
}
void CWindow::SetPos(const CVec2Int& pos)
{
	glfwSetWindowPos(window, pos.x, pos.y);
}
void CWindow::SetPos(const int x, const int y)
{
	glfwSetWindowPos(window, x, y);
}
void CWindow::SetSize(const CVec2Int& size)
{
	Limits(size.x, size.y);
	glfwSetWindowSize(window, size.x, size.y);
}
void CWindow::SetSize(const int w, const int h)
{
	Limits(w, h);
	glfwSetWindowSize(window, w, h);
}
void CWindow::ChengeTitle(const char* windowname)
{
	name = windowname;
	glfwSetWindowTitle(window, name.c_str());
}
void CWindow::ChangeMode(const int x, const int y, const int w, const int h, const bool flag)
{
	SetPos(x, y);
	SetSize(w, h);
	glfwSetWindowMonitor(window, flag ? glfwGetPrimaryMonitor() : NULL, x, y, w, h, GLFW_DONT_CARE);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	CFramework::Get()->GetScene()->GetCamera()->Initialize(CBox2D(0, 0, w, h));

}
void CWindow::ChangeMode(const int x, const int y, const int w, const int h, const char* n, const bool flag)
{
	ChengeTitle(n);
	ChangeMode(x, y, w, h, flag);
}
const std::string& CWindow::GetTitle() const
{
	return name;
}
void CWindow::ChangeMode(const CVec2Int& pos, const CVec2Int& size, const bool flag)
{
	ChangeMode(pos.x, pos.y, size.x, size.y, flag);
}

CWindowParameter::CWindowParameter(const CVec2Int& p, const CVec2Int& s, const char* n, const bool f)
{
	position = p;
	size = s;
	name = n;
	enableFullScreen = f;
}