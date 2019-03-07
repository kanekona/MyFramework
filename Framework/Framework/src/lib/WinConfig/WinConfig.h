#pragma once
#include "Entity\Entity.h"

class WinConfig : public Entity
{
	void Enter() override;
	void Update() override;
public:
	explicit WinConfig();
	virtual ~WinConfig();
};