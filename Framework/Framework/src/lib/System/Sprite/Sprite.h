#pragma once
#include "Entity\Entity.h"
#include "Texture\Texture.h"
class Sprite : public Entity
{
	//! order in layer
	unsigned int order;
	//! Registerd ID
	const int registerd;
	/**
	*@brief	Register this in the RenderingManager
	*/
	void Register();
public:
	//! TextureData
	Texture* texture;
	//! Transform
	Transform* transform;
	//! Color
	Color* color;
	/**
	*@brief	constructor
	*@param[in] bool flag Register in the drawing system
	*@param[in] int registerd Registerd To Number
	*/
	explicit Sprite(const bool flag, const int registerd = REGISTERD_CANVAS);
	/**
	*@brief	destructor
	*/
	virtual ~Sprite();
	/**
	*@brief	ï`âÊÇçsÇ§
	*/
	virtual void Draw();
	/**
	*@brief Set Draw Order
	*@param[in] unsigned int order Order
	*/
	void SetDrawOrder(const unsigned int order);
	/**
	*@brief	Sprite Draw Order Comparsion
	*@param[in] Sprite* first Sprite
	*@param[in] Sprite* second Sprite
	*@return bool true if second is freater than first
	*/
	static bool Comparison(const Sprite* first, const Sprite* second);

	const static int REGISTERD_CANVAS = 0x01;
	const static int REGISTERD_UI = 0x02;
	const static int REGISTERD_BACK = 0x03;
};
const int Sprite::REGISTERD_CANVAS;
const int Sprite::REGISTERD_UI;
const int Sprite::REGISTERD_BACK;