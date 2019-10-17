#pragma once
#include "Entity\Entity.h"

class TextureTestEntity : public CEntity
{
	void Update() override;
	void Entry() override;
public:
	explicit TextureTestEntity();
	virtual ~TextureTestEntity();
};