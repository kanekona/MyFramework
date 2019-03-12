#include "RenderingManager.h"
#include <algorithm>
RenderingManager::RenderingManager()
{

}
RenderingManager::~RenderingManager()
{

}
void RenderingManager::CanvasOrderSort(std::vector<Sprite*>* sortList)
{
	std::sort(sortList->begin(), sortList->end(), Sprite::Comparison);
}
void RenderingManager::CanvasAdaptation(std::vector<Sprite*>*now, std::vector<Sprite*>* plans)
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
void RenderingManager::UIRendering()
{
	for (auto it : uiCanvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void RenderingManager::CanvasRendering()
{
	for (auto it : canvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void RenderingManager::BackRendering()
{
	for (auto it : backCanvas)
	{
		if (it->GetActive())
		{
			it->Draw();
		}
	}
}
void RenderingManager::Render()
{
	this->UIRendering();
	this->CanvasRendering();
	this->BackRendering();
}
void RenderingManager::AllStateAdaptation()
{
	CanvasAdaptation(&uiCanvas, &plansUIs);
	CanvasAdaptation(&canvas, &plansCanvas);
	CanvasAdaptation(&backCanvas, &plansBacks);
}
void RenderingManager::AddSpriteCanvas(Sprite* sprite)
{
	plansCanvas.emplace_back(sprite);
}
void RenderingManager::AddSpriteUI(Sprite* sprite)
{
	plansUIs.emplace_back(sprite);
}
void RenderingManager::AddSpriteBack(Sprite* sprite)
{
	plansBacks.emplace_back(sprite);
}
void RenderingManager::DeleteSpriteCanvas(Sprite* sprite)
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
void RenderingManager::DeleteSpriteUI(Sprite* sprite)
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
void RenderingManager::DeleteSpriteBack(Sprite* sprite)
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
void RenderingManager::Render(RenderingManager* manager)
{
	manager->Render();
}
void RenderingManager::AllSpriteAdaptation(RenderingManager* manager)
{
	manager->AllStateAdaptation();
}