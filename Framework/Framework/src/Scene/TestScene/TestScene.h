#pragma once
#include "Scene\Scene.h"

class TestScene : public Scene
{
	void Enter() override;
public:
	explicit TestScene();
	virtual ~TestScene();
};