#pragma once
#include "Scene\Scene.h"

class WinConfig : public Scene
{
	void Enter() override;
public:
	explicit WinConfig();
	virtual ~WinConfig();
};