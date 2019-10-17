#include "TextureTest.h"
#include "ResourceManager\ResourceManager.h"
#include "Texture\Texture.h"
#include "Texture\ScreenShot.h"
#include "Input\Input.h"
#include "Sprite\Sprite.h"
#include "Engine\EngineMacro.h"
#include "Engine\Framework.h"
#include "Window\Window.h"

void TextureTestEntity::Update()
{
	if (CInput::Get()->down(In::B4))
	{
		CVec2Int Size = CFramework::Get()->GetWindow()->GetSize();
		CScreenShot::Capture(CBox2D(0, 0, Size.x, Size.y / 2));
	}
	CColor MousePixcel = CInput::Get()->mouse->GetPixcel();
	printf("[Pos:%f:%f][%f][%f][%f][%f]\n", CInput::Get()->mouse->GetPos().x, CInput::Get()->mouse->GetPos().y, MousePixcel.red, MousePixcel.green, MousePixcel.blue, MousePixcel.alpha);
}

void TextureTestEntity::Entry()
{
#if DEBUG_ENABLE
	ENSUREMSG(true, "aiueo");
	ENSURE(true);
#endif
	std::string texID = "colortest";
	//std::string texID = "back";
	//data\not\image\2.装飾\使用例\20.たんこぶ.png
	CSprite* sprite = new CSprite();
	sprite->tag = "testSprite";
	SetChildren(sprite);
	sprite->CreateData();
	sprite->texture->Load("./data/not/image/2.装飾/使用例/20.たんこぶ.png");
	sprite->transform->scale = *sprite->texture->GetSize();

	sprite = new CSprite();
	sprite->tag = "testSprite";
	SetChildren(sprite);
	sprite->CreateData();
	sprite->texture->Load("./data/not/image/4.服装・髪型/3.ワンピース/1.png");
	sprite->transform->position.x += 500;
	sprite->transform->scale = *sprite->texture->GetSize();

#if ENGINE_DEBUG
	CResourceManager::Get()->GetTextureData(texID)->OutputPixcelData();
#endif
	CTexture* tex = CResourceManager::Get()->GetTextureData(texID);

	CColor* color = CTexture::NewPixels(tex);

	CTexture::GetPixels(tex, color);

	for (int y = 0; y < tex->GetSize()->y; ++y)
	{
		for (int x = 0; x < tex->GetSize()->x; ++x)
		{
			printf("[%.0f:%.0f:%.0f:%.0f] "
				, color[y * tex->GetSize()->x + x].red
				, color[y * tex->GetSize()->x + x].green
				, color[y * tex->GetSize()->x + x].blue
				, color[y * tex->GetSize()->x + x].alpha
			);
		}
		printf("\n");
	}

	std::vector<std::vector<CColor>> data = CTexture::VectorFromArray(tex, color);

	for (int y = 0; y < data.size(); ++y)
	{
		for (int x = 0; x < data[y].size(); ++x)
		{
			printf("[%.0f:%.0f:%.0f:%.0f] "
				,data[y][x].red
				,data[y][x].green
				,data[y][x].blue
				,data[y][x].alpha
			);
		}
		printf("\n");
	}

	data = CTexture::VectorFromArray(tex, color, 1, 1, 2, 2);

	for (int y = 0; y < data.size(); ++y)
	{
		for (int x = 0; x < data[y].size(); ++x)
		{
			printf("[%.0f:%.0f:%.0f:%.0f] "
				, data[y][x].red
				, data[y][x].green
				, data[y][x].blue
				, data[y][x].alpha
			);
		}
		printf("\n");
	}


	CColor point = CTexture::ColorFromArray(tex, color, 1, 1);
	printf("[%.0f:%.0f:%.0f:%.0f] \n"
		, point.red
		, point.green
		, point.blue
		, point.alpha
	);

	CTexture::FreePixels(color);
}

TextureTestEntity::TextureTestEntity()
{
}

TextureTestEntity::~TextureTestEntity()
{

}
