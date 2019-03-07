#pragma once
#include "Scene\Scene.h"

class StartScene : public Scene
{
	void Enter() override;
public:
	explicit StartScene();
	virtual ~StartScene();
};