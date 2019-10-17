#include "RenderingManager.h"
#include <algorithm>
CRenderingManager::CRenderingManager()
{

}
CRenderingManager::~CRenderingManager()
{

}
void CRenderingManager::CanvasOrderSort(std::vector<CSprite*>* sortList)
{
	std::sort(sortList->begin(), sortList->end(), CSprite::Comparison);
}
void CRenderingManager::CanvasAdaptation(std::vector<CSprite*>*now, std::vector<CSprite*>* plans)
{
	for (auto it = now->begin(); it != now->end();)
	{
		if (*it != nullptr)
		{
			++it;
		}
		else
		{
			it = now->erase(it);
		}
	}
	if (plans->size())
	{
		for (auto it : *plans)
		{
			now->emplace_back(it);
		}
		plans->clear();
		CanvasOrderSort(now);
	}
}
void CRenderingManager::UIRendering()
{
	for (auto it : uiCanvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void CRenderingManager::CanvasRendering()
{
	for (auto it : canvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void CRenderingManager::BackRendering()
{
	for (auto it : backCanvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void CRenderingManager::Render()
{
	UIRendering();
	CanvasRendering();
	BackRendering();
}
void CRenderingManager::AllStateAdaptation()
{
	CanvasAdaptation(&uiCanvas, &plansUIs);
	CanvasAdaptation(&canvas, &plansCanvas);
	CanvasAdaptation(&backCanvas, &plansBacks);
}
void CRenderingManager::AddSpriteCanvas(CSprite* sprite)
{
	plansCanvas.emplace_back(sprite);
}
void CRenderingManager::AddSpriteUI(CSprite* sprite)
{
	plansUIs.emplace_back(sprite);
}
void CRenderingManager::AddSpriteBack(CSprite* sprite)
{
	plansBacks.emplace_back(sprite);
}
void CRenderingManager::DeleteSpriteCanvas(CSprite* sprite)
{
	for (auto it = canvas.begin(); it != canvas.end();)
	{
		if (*it == sprite)
		{
			canvas.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}
void CRenderingManager::DeleteSpriteUI(CSprite* sprite)
{
	for (auto it = uiCanvas.begin(); it != uiCanvas.end();)
	{
		if (*it == sprite)
		{
			uiCanvas.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}
void CRenderingManager::DeleteSpriteBack(CSprite* sprite)
{
	for (auto it = backCanvas.begin(); it != backCanvas.end();)
	{
		if (*it == sprite)
		{
			backCanvas.erase(it);
			return;
		}
		else
		{
			++it;
		}
	}
}
void CRenderingManager::Render(CRenderingManager* manager)
{
	manager->Render();
}
void CRenderingManager::AllSpriteAdaptation(CRenderingManager* manager)
{
	manager->AllStateAdaptation();
}