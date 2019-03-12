#pragma once
//#include "Entity/Entity.h"
#include "Sprite\Sprite.h"
#include <vector>
/**
*@brief	•`‰æ‚ğ‚Ü‚Æ‚ß‚Äs‚¤class
•`‰æ‡‚ğ‚Ü‚Æ‚ß‚é‚±‚Æ‚ğl‚¦‚é‚Æ“o˜^—p•Ï”‚ª‚ ‚Á‚½•û‚¢‚¢‚©‚È

*/
class RenderingManager
{
	//! Front Canvas
	std::vector<Sprite*> uiCanvas;
	//! Canvas
	std::vector<Sprite*> canvas;
	//! Back Canvas
	std::vector<Sprite*> backCanvas;
	//! Plans Front Canvas
	std::vector<Sprite*> plansUIs;
	//! Plans Canvas
	std::vector<Sprite*> plansCanvas;
	//! Plans Back Canvas
	std::vector<Sprite*> plansBacks;
	/**
	*@brief	order sort
	*/
	void CanvasOrderSort(std::vector<Sprite*>* sortList);
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
	void CanvasAdaptation(std::vector<Sprite*>* now, std::vector<Sprite*>* plans);
public:
	/**
	*@brief	constructor
	*/
	explicit RenderingManager();
	/**
	*@brief destructor
	*/
	virtual ~RenderingManager();
	/**
	*@brief	Add Sprite to Canvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteCanvas(Sprite* sprite);
	/**
	*@brief	Add Sprite to UICanvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteUI(Sprite* sprite);
	/**
	*@brief	Add Sprite to BackCanvas
	*@param[in] Sprite* sprite Add Data
	*/
	void AddSpriteBack(Sprite* sprite);

	/**
	*@brief	Delete Sprite to Canvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteCanvas(Sprite* sprite);
	/**
	*@brief	Delete Sprite to UICanvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteUI(Sprite* sprite);
	/**
	*@brief	Delete Sprite to BackCanvas
	*@param[in] Sprite* sprite Delete Data
	*/
	void DeleteSpriteBack(Sprite* sprite);

	/**
	*@brief	AllCanvasRendering
	*@param[in] RenderingManager* renderingManager this
	*/
	static void Render(RenderingManager* renderingManager);
	/**
	*@brief	All Sprite Adaptation
	*@param[in] RenderingManager* renderingManager this
	*/
	static void AllSpriteAdaptation(RenderingManager* renderingManager);
};