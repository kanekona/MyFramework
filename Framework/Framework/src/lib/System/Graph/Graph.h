#pragma once
#include "System\System.h"
#include "Engine\Data.h"
#include "Sprite\Sprite.h"
#include <vector>
#include "Engine\EngineTypedef.h"
class CShader;

class CGraph : public CSprite
{
	CBox2D Window;
	//! グラフの縦横の数値の最大値
	CVec2 MaxSize;
	std::vector<int32> ValueData;
	float lineWidth;
	CColor lineColor;
	CShader* shader;

	void Entry() override;
	void Update() override;
	void Draw() override;
public:
	CGraph();
	virtual ~CGraph();
	void SetMaxWidth(uint16 Width);
	void SetMaxHeight(uint16 Height);
	void SetWindowForm(const CBox2D& Form);
	void SetData(std::vector<int32>& InData);
	void Add(int32 InAdd);
};