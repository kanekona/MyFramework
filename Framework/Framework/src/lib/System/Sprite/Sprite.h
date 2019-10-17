#pragma once
#include "Entity\Entity.h"
#include "Engine\EngineTypedef.h"

class CTexture;
class CColor;
class CTransform;
class CShader;

class CSprite : public CEntity
{
	//! order in layer
	unsigned int order;
	//! Registerd ID
	const int registerd;
	//! delete data with destructor
	bool IsDeleteData;
	/**
	*@brief	Register this in the RenderingManager
	*/
	virtual void Register();
	/**
	*@brief 
	*/
	virtual void Release();
public:
	//! TextureData
	CTexture* texture;
	//! Transform
	CTransform* transform;
	//! Color
	CColor* color;
	/**
	*@brief	constructor
	*@param[in] bool flag Register in the drawing system
	*@param[in] int registerd Registerd To Number
	*/
	explicit CSprite(const bool flag = true, const int registerd = REGISTERD_CANVAS);
	/**
	*@brief	destructor
	*/
	virtual ~CSprite();
	/**
	*@brief	ï`âÊÇçsÇ§
	*/
	virtual void Draw();
	/**
	*@brief	SetShaderValue
	*@param[in] Shader* shader Use Shader
	*/
	virtual void SetShaderData(CShader* shader);
	/**
	*@brief Set Draw Order
	*@param[in] unsigned int order Order
	*/
	virtual void SetDrawOrder(const unsigned int order);
	/**
	*@brief	Sprite Draw Order Comparsion
	*@param[in] Sprite* first Sprite
	*@param[in] Sprite* second Sprite
	*@return bool true if second is freater than first
	*/
	static bool Comparison(const CSprite* first, const CSprite* second);
	/**
	*@brief New 3 Member
	*/
	void CreateData();
	/**
	*@brief	Delete 3 Member
	*/
	void DeleteData();

	const static uint8 REGISTERD_CANVAS = 0x01;
	const static uint8 REGISTERD_UI = 0x02;
	const static uint8 REGISTERD_BACK = 0x03;
};
const uint8 CSprite::REGISTERD_CANVAS;
const uint8 CSprite::REGISTERD_UI;
const uint8 CSprite::REGISTERD_BACK;