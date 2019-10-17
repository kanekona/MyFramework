#pragma once
#include "Scene\Scene.h"

class TestScene : public CScene
{
	void Entry() override;
public:
	explicit TestScene();
	virtual ~TestScene();
};