#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Timer\glTimer.h"

class CSceneManager;
class CScene;
class CWindow;

/**
*@brief Game Framework
*/
class CFramework : private CNonCopyable
{
	//! Scene Manager
	CSceneManager* sceneManager;
	//! Window
	CWindow* window;
	//! Enable Engine Destroy
	bool* enableEngineDestroy;
	//! Timer
	CTime time;
	//! preTime
	float preTime;
	//! DeltaTime
	float deltaTime;
	//! FrameworkInstance
	static CFramework* instance;
	/**
	*@brief	constructor
	*@param[in] bool* destroy Engine Destroy Frag Address
	*/
	explicit CFramework(bool* destroy);
	/**
	*@brief	destructor
	*/
	virtual ~CFramework();
public:
	/**
	*@brief Get FrameworkInstance
	*@return Framework* Instance
	*/
	static CFramework* Get();
	/**
	*@brief	Create Framework Instance
	*@param[in] bool* destroy Engine Destroy Frag Address
	*@return Framework* Get Framework Instance
	*@detail ä˘Ç…ê∂ê¨Ç≥ÇÍÇƒÇ¢ÇÈèÍçáÇÕâΩÇ‡çsÇ¢Ç‹ÇπÇÒ
	*/
	static CFramework* Create(bool* destroy);
	/**
	*@brief	Instance Destroy
	*/
	static void Destroy();
	/**
	*@brief Change Next Scene
	*@param[in] Scene* next NextScene
	*/
	void ChangeScene(CScene* next);
	/**
	*@brief	Get Now Scene
	*@return Scene* Now Scene
	*/
	static CScene* GetScene();
	/**
	*@brief	Get Window
	*/
	static CWindow* GetWindow();
	/**
	*@brief Framework Update
	*/
	void Update();
	/**
	*@brief	Engine Destroy
	*/
	void EngineDestroy();
	/**
	*@brief	Create SceneManager
	*@param[in] Scene* begin Start Scene
	*/
	void CreateSceneManager(CScene* begin);
	/**
	*@brief Get Position In The Window
	*@param[in] unsigned int x X Coordinate Split
	*@param[in] unsigned int y Y Coordinate Split
	*@param[in] unsigned int number Split Number
	*@return Vec2Int In The Window Position
	*/
	CVec2Int GetPosition(const unsigned int x, const unsigned int y, const unsigned int number);
	/**
	*@brief Get Size In The Window
	*@param[in] unsigned int x X Coordinate Split
	*@param[in] unsigned int y Y Coordinate Split
	*@return Vec2Int In The Window Size
	*/
	CVec2Int GetSize(const unsigned int x, const unsigned int y);
	/**
	*@brief Get Size In The Window
	*@param[out] float* out float[2]
	*/
	void GetSize(float* out);
	/**
	*@brief	Get DeltaTime
	*@return float deltaTime
	*/
	float DeltaTime() const;
};
