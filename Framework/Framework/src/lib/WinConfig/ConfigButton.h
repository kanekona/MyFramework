#pragma once
#include "Button\Button.h"

class ConfigButton : public Button
{
	void Decision() override;
	bool enable;	
public:
	explicit ConfigButton(const Transform& transform, const bool enableFullscreen);
	virtual ~ConfigButton();
};