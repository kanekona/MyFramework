#pragma once
#include "Entity\Entity.h"
#include "Texture\Texture.h"
class Sprite : public Entity
{
	//! order in layer
	unsigned int order;
	/**
	*@brief	Register this in the RenderingManager
	*@param[in] int registerd Registerd To Number
	*/
	void Register(const int registerd);
public:
	//! TextureData
	Texture* texture;
	//! Transform
	Transform* transform;
	//! Color
	Color* color;
	/**
	*@brief	constructor
	*/
	explicit Sprite(const int registerd = REGISTERD_CANVAS);
	/**
	*@brief	destructor
	*/
	virtual ~Sprite();
	/**
	*@brief	ï`âÊÇçsÇ§
	*/
	virtual void Draw();
	const static int REGISTERD_CANVAS = 0x01;
	const static int REGISTERD_UI = 0x02;
	const static int REGISTERD_BACK = 0x03;
};
const int Sprite::REGISTERD_CANVAS;
const int Sprite::REGISTERD_UI;
const int Sprite::REGISTERD_BACK;