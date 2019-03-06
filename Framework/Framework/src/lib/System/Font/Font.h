
#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H

#include "Texture\Texture.h"
#include "Sprite\Sprite.h"
#include <map>
/**
*@ Font Class
* 描画するテキストとサイズは事前に登録しておく
*/
class Font : public Sprite
{
public:
	//こいつが文字１つのデータを保持する感じが理想
	struct TextureData
	{
		Texture* texture;
		Vec2Int size;
		Vec2Int bearing;
		wchar_t character;
	};
	void Draw() override;
private:
	std::map<char, TextureData> data;
	GLuint texID;
	FT_Library ft_library;
	FT_Face face;
	std::string text;
	unsigned int size;
public:
	explicit Font();
	virtual ~Font();
	void SetText(const std::string& text);
	/**
	*使用禁止
	*/
	void SetText(const std::string& text, unsigned int* offset);
	std::string GetText() const;
	void SetSize(const unsigned int fontSize);
	unsigned int GetSize() const;
	//std::vector<TextureData>* GetData();
	std::map<char, TextureData>* GetData();
};