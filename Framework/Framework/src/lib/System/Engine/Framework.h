#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include "Timer\glTimer.h"

class SceneManager;
class Scene;
class Window;

/**
*@brief Game Framework
*/
class Framework : private NonCopyable
{
	//! Scene Manager
	SceneManager* sceneManager;
	//! Window
	Window* window;
	//! Enable Engine Destroy
	bool* enableEngineDestroy;
	//! Timer
	Time time;
	//! preTime
	float preTime;
	//! DeltaTime
	float deltaTime;
	//! FrameworkInstance
	static Framework* instance;
	/**
	*@brief	constructor
	*@param[in] bool* destroy Engine Destroy Frag Address
	*/
	explicit Framework(bool* destroy);
	/**
	*@brief	destructor
	*/
	virtual ~Framework();
public:
	/**
	*@brief Get FrameworkInstance
	*@return Framework* Instance
	*/
	static Framework* Get();
	/**
	*@brief	Create Framework Instance
	*@param[in] bool* destroy Engine Destroy Frag Address
	*@return Framework* Get Framework Instance
	*@detail ä˘Ç…ê∂ê¨Ç≥ÇÍÇƒÇ¢ÇÈèÍçáÇÕâΩÇ‡çsÇ¢Ç‹ÇπÇÒ
	*/
	static Framework* Create(bool* destroy);
	/**
	*@brief	Instance Destroy
	*/
	static void Destroy();
	/**
	*@brief Change Next Scene
	*@param[in] Scene* next NextScene
	*/
	void ChangeScene(Scene* next);
	/**
	*@brief	Get Now Scene
	*@return Scene* Now Scene
	*/
	Scene* GetScene();
	/**
	*@brief	Get Window
	*/
	Window* GetWindow();
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
	void CreateSceneManager(Scene* begin);
	/**
	*@brief Get Position In The Window
	*@param[in] unsigned int x X Coordinate Split
	*@param[in] unsigned int y Y Coordinate Split
	*@param[in] unsigned int number Split Number
	*@return Vec2Int In The Window Position
	*/
	Vec2Int GetPosition(const unsigned int x, const unsigned int y, const unsigned int number);
	/**
	*@brief Get Size In The Window
	*@param[in] unsigned int x X Coordinate Split
	*@param[in] unsigned int y Y Coordinate Split
	*@return Vec2Int In The Window Size
	*/
	Vec2Int GetSize(const unsigned int x, const unsigned int y);
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
