#include "TextureTest.h"
#include "ResourceManager\ResourceManager.h"
#include "Texture\ScreenShot.h"
#include "Input\Input.h"
#include "Sprite\Sprite.h"

void TextureTestEntity::Update()
{
	if (Input::Get()->down(In::B4))
	{
		ScreenShot::Capture();
	}
}

void TextureTestEntity::Enter()
{
	std::string texID = "colortest";
	//std::string texID = "back";
	//data\not\image\2.装飾\使用例\20.たんこぶ.png
	Sprite* sprite = new Sprite();
	sprite->tag = "testSprite";
	SetChildren(sprite);
	sprite->CreateData();
	sprite->texture->Load("./data/not/image/2.装飾/使用例/20.たんこぶ.png");
	sprite->transform->scale = *sprite->texture->GetSize();

	ResourceManager::Get()->GetTextureData(texID)->OutputPixcelData();

	Texture* tex = ResourceManager::Get()->GetTextureData(texID);

	Color* color = Texture::NewPixels(tex);

	Texture::GetPixels(tex, color);

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

	std::vector<std::vector<Color>> data = Texture::VectorFromArray(tex, color);

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

	data = Texture::VectorFromArray(tex, color, 1, 1, 2, 2);

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


	Color point = Texture::ColorFromArray(tex, color, 1, 1);
	printf("[%.0f:%.0f:%.0f:%.0f] \n"
		, point.red
		, point.green
		, point.blue
		, point.alpha
	);

	Texture::FreePixels(color);
}

TextureTestEntity::TextureTestEntity()
{
}

TextureTestEntity::~TextureTestEntity()
{
	GetChild<Sprite>("testSprite")->DeleteData();
}
