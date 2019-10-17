#pragma once
#include "Button\Button.h"

class ConfigButton : public CButton
{
	void Decision() override;
	bool enable;	
public:
	explicit ConfigButton(const CTransform& transform, const bool enableFullscreen);
	virtual ~ConfigButton();
};