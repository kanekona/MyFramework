#include "Graph.h"
#include "Engine\OGF.hpp"
#include "ResourceManager\ResourceManager.h"
void CGraph::Entry()
{
	shader = CResourceManager::Get()->GetShaderData("line");
}

void CGraph::Update()
{
}

void CGraph::Draw()
{
	for (int i = 1; i < ValueData.size(); ++i)
	{	
		CVec2 begin = { 
			(i - 1) * (Window.w / ValueData.size()) + Window.x,
			(ValueData[i - 1] / Window.h * Window.h) + Window.y
		};
		CVec2 end = {
			i * (Window.w / ValueData.size()) + Window.x, 
			(ValueData[i] / Window.h * Window.h) + Window.y
		};
		COGF::Draw(shader, &begin, &end, &lineColor);
	}
}

CGraph::CGraph()
{

}

CGraph::~CGraph()
{
}

void CGraph::SetMaxWidth(uint16 Width)
{
	MaxSize.x = Width;
}

void CGraph::SetMaxHeight(uint16 Height)
{
	MaxSize.y = Height;
}

void CGraph::SetWindowForm(const CBox2D & Form)
{
	Window = Form;
}

void CGraph::SetData(std::vector<int32>& InData)
{
	ValueData = InData;
}

void CGraph::Add(int32 InAdd)
{
	ValueData.emplace_back(InAdd);
}
