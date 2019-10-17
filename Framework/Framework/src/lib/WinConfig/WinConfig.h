#pragma once
#include "Entity\Entity.h"

class WinConfig : public CEntity
{
	void Entry() override;
	void Update() override;
public:
	explicit WinConfig();
	virtual ~WinConfig();
};