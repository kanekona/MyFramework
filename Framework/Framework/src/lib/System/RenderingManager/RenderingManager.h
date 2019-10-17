#pragma once
//#include "Entity/Entity.h"
#include "Sprite\Sprite.h"
#include <vector>
/**
*@brief	•`‰æ‚ğ‚Ü‚Æ‚ß‚Äs‚¤class
•`‰æ‡‚ğ‚Ü‚Æ‚ß‚é‚±‚Æ‚ğl‚¦‚é‚Æ“o˜^—p•Ï”‚ª‚ ‚Á‚½•û‚¢‚¢‚©‚È

*/
class CRenderingManager
{
	//! Front Canvas
	std::vector<CSprite*> uiCanvas;
	//! Canvas
	std::vector<CSprite*> canvas;
	//! Back Canvas
	std::vector<CSprite*> backCanvas;
	//! Plans Front Canvas
	std::vector<CSprite*> plansUIs;
	//! Plans Canvas
	std::vector<CSprite*> plansCanvas;
	//! Plans Back Canvas
	std::vector<CSprite*> plansBacks;
	/**
	*@brief	order sort
	*/
	void CanvasOrderSort(std::vector<CSprite*>* sortList);
	/**
	*@brief UIRendering
	*/
	void UIRendering();
	/**
	*@brief	CanvasRendering
	*/
	void CanvasRendering();
	/**
	*@brief	BackRendering
	*/
	void BackRendering();
	/**
	*@brief	Rendering
	*/
	void Render();
	/**
	*@brief	All Sprite Adaptation
	*/
	void AllStateAdaptation();
	/**
	*@brief	Canvas Sprite Adaptation
	*/
	void CanvasAdaptation(std::vector<CSprite*>* now, std::vector<CSprite*>* plans);
public:
	/**
	*@brief	constructor
	*/
	explicit CRenderingManager();
	/**
	*@brief destructor
	*/
	virtual ~CRenderingManager();
	/**
	*@brief	Add Sprite to Canvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteCanvas(CSprite* sprite);
	/**
	*@brief	Add Sprite to UICanvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteUI(CSprite* sprite);
	/**
	*@brief	Add Sprite to BackCanvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteBack(CSprite* sprite);

	/**
	*@brief	Delete Sprite to Canvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteCanvas(CSprite* sprite);
	/**
	*@brief	Delete Sprite to UICanvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteUI(CSprite* sprite);
	/**
	*@brief	Delete Sprite to BackCanvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteBack(CSprite* sprite);

	/**
	*@brief	AllCanvasRendering
	*@param[in] RenderingManager* renderingManager this
	*/
	static void Render(CRenderingManager* renderingManager);
	/**
	*@brief	All Sprite Adaptation
	*@param[in] RenderingManager* renderingManager this
	*/
	static void AllSpriteAdaptation(CRenderingManager* renderingManager);
};