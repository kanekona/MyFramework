#pragma once
#include "Entity\Entity.h"
#include "Graph\Graph.h"
#include "StrID\StrID.h"

class GraphTest : public CEntity
{
	void Update() override;
	void Entry() override;
public:
	explicit GraphTest();
	virtual ~GraphTest();
};