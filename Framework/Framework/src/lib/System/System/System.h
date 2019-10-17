#pragma once

#include "Engine\EngineMacro.h"
#include "Engine\EngineTypedef.h"

#if !DEBUG_ENABLE
// Degub版のみコンソールを表示する設定
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
#endif

// Windows:GLEWをスタティックライブラリ形式で利用
#define GLEW_STATIC
// GLFWのヘッダ内で他のライブラリを取り込む	
#define GLFW_INCLUDE_GLEXT
#define GLFW_INCLUDE_GLU

#define GLM_SWIZZLE
#define GLM_FORCE_SWIZZLE

//GLM警告
#pragma warning (disable : 4201)
//type_traits警告
#pragma warning (disable : 4239)
//xutility警告
#pragma warning (disable : 4244)
//stb_image警告
#pragma warning (disable : 4100)

#pragma comment(lib, "OPENGL32.lib")
#pragma comment(lib, "GLU32.lib")
#pragma comment(lib, "Win64/OpenAL32.lib")
//OpenCV
#pragma comment(lib, "opencv_core342.lib")
#pragma comment(lib, "opencv_videoio342.lib")
//LNK4098
#pragma comment(lib, "freetype.lib")
//FFTW
#pragma comment(lib, "libfftw3-3.lib")
#pragma comment(lib, "libfftw3f-3.lib")
#pragma comment(lib, "libfftw3l-3.lib")

#if defined(_MSC_VER)
// Windows:外部ライブラリのリンク指定
#if DEBUG_ENABLE
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3d.lib")
#else
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#endif
#endif

//数値演算定数
#define _USE_MATH_DEFINES
//小数点誤差修正
#define _OX_EPSILON_ 0.0000001f

#define PI 3.1415926f

#define STR(var) #var

//GLM
//#include <glm/glm.hpp>

#if WINDOWS_BUILD
#include <Windows.h>
#endif

#if defined(_MSC_VER)
//EWを先にインクルードする必要がある。
#include <GL/glew.h>
#endif
//GLFW
#include <GLFW/glfw3.h>
//OpenAL
#include "al\al.h"
#include "al\alc.h"
//OpenCV
#include "opencv2\opencv.hpp"
//FFTW
#include "fftw3.h"

#include "Engine\Data.h"
#include "StrID\StrID.h"
#include "randmais.h"
#include <vector>

/**
*namespace KL
*@brief	便利機能関数や数学計算
*/
namespace KL
{
	void MulitMatrixf(GLfloat*, GLfloat*, GLfloat*);
	void Normalize(GLfloat*);
	void Rotate(const float _angle, CVec2*);
	void LineBoxDraw(const CBox2D* box, const CColor& color = { 1,1,1,1 }, const float linewidth = 1.0f);
	void LineBoxDraw(const CBox2D* box, const float linewidth, const CColor& color = { 1,1,1,1 });
	void LineBoxDraw(const CVec2* vec, const CColor& color = { 1,1,1,1 }, const float linewidth = 1.0f);
	void LineBoxDraw(const CVec2* vec, const float linewidth, const CColor& color = { 1,1,1,1 });
	void LineDraw(const CVec2* vec, const CColor& color = { 1,1,1,1 }, const float linewidth = 1.0f);
	void LineDraw(const CVec2* vec, const float linewidth, const CColor& color = { 1,1,1,1 });
	void LineOvalDraw(const int x, const int y, const float ovalx, const float ovaly, const float linewidth = 1.0f, const CColor& color = { 1,1,1,1 });
	void LineOvalDraw(const CVec2* pos, const CVec2* scale, const float linewidth = 1.0f, const CColor& color = { 1,1,1,1 });
	void PointDraw(const CVec2* pos, const float linewidth, const CColor& color = { 1,1,1,1 });
	void PointDraw(const CVec2* pos, const CColor& color = { 1,1,1,1 }, const float linewidth = 1.0f);
	void BackColor(const CColor& color);
	void BackColor(const float&red, const float&green, const float&blue, const float&alpha);
	int mbclen(const char* c);
	void cout(const CBox2D&);
	void cout(const CVec2&);
	void cout(const CColor&);
	void cout(const CVec3&);
	bool Data_Cipher(const std::string& in_path, const std::string& out_path);
	std::string Data_Composite(std::ifstream& ifs);
	void OutDebugData(const std::string& out_path, const std::string& text);
	void DataClear(const std::string& path);
	bool CheckText(std::string* first, std::string* second);
	void FileCreate(const std::string& path, std::vector<std::string>& data);
	bool StringisNumber(const std::string& str);
	bool StringFromNumber(const std::string& str, float* out);
	bool StringFromNumber(const std::string& str, int* out);
	bool StringFromStrID(const std::string& str, CStrID* out);
	unsigned int Count(const std::string& str, const char c);
	std::string* SplitString(const std::string& text, const char c, int* out);
	void SplitString(std::vector<std::string>* out, const std::string& text, const char c);
	void Trim(std::string* str, const char c);
	void Trim(std::string* str, const std::string& trim);
	bool Split(const std::string& text, const std::string& find, std::string* outLeft, std::string* outRigth);
	bool Split(const std::string& text, const char find, std::string* outLeft, std::string* outRigth);
	template<class T> std::string ClassFromName()
	{
		std::string name = typeid(T).name();
		Trim(&name, "class ");
		return name;
	}
	template<class T> void ClassFromName(std::string* out)
	{
		*out = typeid(T).name();
		Trim(out, "class ");
	}
	template<class T> void ClassFromName(CStrID* out)
	{
		std::string classname;
		classname = typeid(T).name();
		Trim(&classname, "class ");
		*out = CStrID(classname);
	}
	template<typename T> void StructFromName(std::string* out)
	{
		*out = typeid(T).name();
		Trim(out, "struct ");
	}
}