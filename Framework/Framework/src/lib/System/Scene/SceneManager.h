#pragma once
#include "NonCopyable\NonCopyable.hpp"

class CScene;

class CSceneManager : private CNonCopyable
{
	CScene* nowScene;
	CScene* nextScene;
	/**
	*@brief Scene Change Adaptation
	*/
	void ChangeAdaptation();
public:
	/**
	*@brief	Scene Change
	*@param[in] Scene* nextScene NextScene
	*/
	void ChangeScene(CScene* nextScene);
	/**
	*@brief Scene Update
	*/
	void SceneUpdate();
	/**
	*@brief Get Now Scene
	*@return Scene* Now Scene
	*/
	CScene* Get();
	/**
	*@brief	constructor
	*@param[in] Scene* begin Start Scene
	*/
	explicit CSceneManager(CScene* begin);
	/**
	*@brief	destructor
	*/
	virtual ~CSceneManager();
};