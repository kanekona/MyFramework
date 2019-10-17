
#pragma once
#include "System\System.h"
#include "Engine\Data.h"
#include "NonCopyable\NonCopyable.hpp"
class CWindowParameter;
class CWindow;
/**
*@brief	Windowの生成、管理を行うclass
*/
class CWindow : private CNonCopyable
{
	//! アイコン情報
	GLFWimage image[1];	
	//! アイコン画像のID
	GLuint id;
	//! ウィンドウのアイコン化状況
	bool enableIcon;
	//! 可視化状況
	bool isVisualization;
	//! 幅
	int widht;
	//! 高さ
	int height;
	//! Windowの名
	std::string name;
	//! フルスク設定
	bool enableFullScreen;
	//! Windowの位置
	CVec2Int position;
	//! Window情報
	GLFWwindow *window;	
public:
	/**
	*@brief	constructor
	*/
	explicit CWindow();
	/**
	*@brief	constructor
	*@param[in]	int x windowXサイズ
	*@param[in] int y windowYサイズ
	*@param[in]	char* name window名
	*@param[in] bool flag フルスク設定
	*@param[in]	Vec2Int pos window位置
	*/
	explicit CWindow(
		const int x,
		const int y,
		const char* name,
		const bool flag,
		const CVec2Int& pos);
	/**
	*@brief	destructor
	*/
	virtual ~CWindow();
	/**
	*@brief	Create Window
	*@param[in]	int x windowXサイズ
	*@param[in] int y windowYサイズ
	*@param[in]	char* name window名
	*@param[in] bool flag フルスク設定
	*@param[in]	Vec2Int pos window位置
	*@return bool 生成に成功でtrue
	*/
	bool Create(
		const int x,
		const int y,
		char* name,
		const bool flag,
		const CVec2Int& pos);
	/**
	*@brief	Create Window
	*@param[in] WindowParameter windowParameter
	*@return bool 生成に成功でtrue
	*/
	bool Create(const CWindowParameter& windowParameter);
	/**
	*@brief	Create Window
	*@return bool 生成に成功でtrue
	*/
	bool Create();
	/**
	*@brief	アイコンを設定する
	*@param[in]	string path ファイルパス
	*/
	void SetIcon(const std::string& path);
	/**
	*@brief	Windowのサイズとアスペクト比を固定する
	*/
	void Limits();
	/**
	*@brief	Windowのサイズとアスペクト比を固定する
	*@param[in]	int w WindowSize_w
	*@param[in]	int h WindowSize_h
	*/
	void Limits(const int w, const int h);
	/**
	*@brief	Windowをアイコン化、アイコン化から解除する
	*/
	void Enable();
	/**
	*@brief	Windowを可視化、可視化から解除する
	*/
	void Visualization();
	/**
	*@brief	マウスを表示させるかを決める
	*@param[in]	bool flag 表示設定
	*/
	void InMouseMode(const bool flag);
	/**
	*@brief	Windowのサイズを返す
	*@return Vec2Int Windowのサイズ
	*/
	CVec2Int GetSize() const;
	/**
	*@brief	Windowの位置を返す
	*@return Vec2Int Windowの位置
	*/
	CVec2Int GetPos() const;
	/**
	*@brief	生成するWindowの位置を設定する
	*@param[in]	Vec2Int pos Windowの位置
	*/
	void CreatePosition(const CVec2Int& pos);
	/**
	*@brief	Window情報を返す
	*@return GLFWWinfow* Window情報
	*/
	GLFWwindow* GetFWWindow() const;
	/**
	*@brief	Windowの位置を設定する
	*@param[in]	const Vec2Int& pos 位置
	*/
	void SetPos(const CVec2Int& pos);
	/**
	*@brief	Windowの位置を設定する
	*@param[in]	int x WindowPosition_x
	*@param[in]	int y WindowPosition_y
	*/
	void SetPos(const int x, const int y);
	/**
	*@brief	Windowのサイズを設定する
	*@param[in]	const Vec2Int& size サイズ
	*/
	void SetSize(const CVec2Int& size);
	/**
	*@brief	Windowのサイズを設定する
	*@param[in]	int w WindowSize_w
	*@param[in]	int h WindowSize_h
	*/
	void SetSize(const int w,const int h);
	/**
	*@brief	ChengeWindowTitle
	*@param[in]	const char* name TitleName
	*/
	void ChengeTitle(const char* name);
	/**
	*@brief	Windowモードを変更
	*@param[in]	int x WindowPosition_x
	*@param[in]	int y WindowPosition_y
	*@param[in]	int w WindowSize_x
	*@param[in]	int h WindowSize_h
	*@param[in]	bool flag true hullScreen
	*/
	void ChangeMode(const int x,const int y,const int w, const int h, const bool flag);
	/**
	*@brief	Windowモードを変更
	*@param[in]	const Vec2Int& pos WindowPosition
	*@param[in]	const Vec2Int& size WindowSize
	*@param[in]	bool flag true fullScreen
	*/
	void ChangeMode(const CVec2Int& pos, const CVec2Int& size, const bool flag);
	/**
	*@brief	Windowモードを変更
	*@param[in]	int x WindowPosition_x
	*@param[in]	int y WindowPosition_y
	*@param[in]	int w WindowSize_x
	*@param[in]	int h WindowSize_h
	*@param[in] const char* name WindowName
	*@param[in]	bool flag true hullScreen
	*/
	void ChangeMode(const int x, const int y, const int w, const int h, const char* name, const bool flag);
	/**
	*@brief WindowTitleを取得する
	*@return const char* WindowTitle
	*/
	const std::string& GetTitle() const;
};
class CWindowParameter
{
public:
	CVec2Int position;
	CVec2Int size;
	const char* name;
	bool enableFullScreen;
	CWindowParameter(const CVec2Int& pos, const CVec2Int& scale, const char* name, const bool screen);
};