#pragma once
#include "Scene\Scene.h"

class StartScene : public CScene
{
	void Entry() override;
public:
	explicit StartScene();
	virtual ~StartScene();
};