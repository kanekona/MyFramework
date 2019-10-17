#include "GraphTest.h"
#include "Engine\Framework.h"
#include "Window\Window.h"

void GraphTest::Update()
{
}

void GraphTest::Entry()
{
	CGraph* graph = new CGraph();
	graph->SetWindowForm(CBox2D(CVec2Int(0, 0), CFramework::Get()->GetWindow()->GetSize()));
	for (uint16 i = 0; i < 960; ++i)
	{
		graph->Add(i);
	}
	SetChildren(graph);
}

GraphTest::GraphTest()
{
}

GraphTest::~GraphTest()
{
}
