#include "ConfigButton.h"
#include "Input\Input.h"
ConfigButton::ConfigButton(const Transform& transform,const bool enableFullscreen)
	:Button(transform)
{
	enable = enableFullscreen;
}
ConfigButton::~ConfigButton()
{

}
void ConfigButton::Decision()
{

}