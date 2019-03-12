#include "Font.h"
#include "Engine\OGF.hpp"

Font::Font()
	:Sprite(Sprite::REGISTERD_CANVAS)
{
	FT_Init_FreeType(&this->ft_library);
	if (!this->ft_library)
	{
		std::cout << "FontInitError" << std::endl;
		return;
	}
	FT_New_Face(this->ft_library, "data/font/msgothic.ttc", 0, &this->face);
	size = 8.0f;
}
Font::~Font()
{
	for (auto& it : this->data)
	{
		delete it.second.texture;
	}
	this->data.clear();
	FT_Done_Face(this->face);
	FT_Done_FreeType(this->ft_library);
}
void Font::SetText(const std::u32string& t)
{
	this->text = t;
	for (auto c : text)
	{
		if (this->data.count(c) == 0)
		{
			FT_Set_Pixel_Sizes(this->face, size, size);
			FT_Get_Char_Index(this->face, c);
			FT_Load_Char(this->face, c, FT_LOAD_RENDER);
			FT_Render_Glyph(this->face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);

			FT_Bitmap bitmap = this->face->glyph->bitmap;
			TextureData d;
			d.character = c;
			d.texture = new Texture();
			d.size = { (int)bitmap.width,(int)bitmap.rows };
			d.bearing = { face->glyph->bitmap_left,face->glyph->bitmap_top };
			d.texture->SetBuffer(bitmap.buffer, bitmap.width, bitmap.rows);
			d.texture->LoadShader("font");
			this->data.insert(std::make_pair(c,d));
		}
	}
}
//void Font::SetText(const std::string& t,unsigned int* offset)
//{
	//this->text = t;
	//unsigned int i = 0;
	//for (auto c : text)
	//{
	//	//ƒf[ƒ^‚É‚È‚¢•¶Žš‚È‚ç’Ç‰Á‚·‚é
	//	//if (this->Check(t))
	//	{
	//		/*FT_Set_Pixel_Sizes(this->face, size + offset[i], size + offset[i]);
	//		FT_Get_Char_Index(this->face, t);
	//		FT_Load_Char(this->face, t, FT_LOAD_RENDER);
	//		FT_Render_Glyph(this->face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);

	//		FT_Bitmap bitmap = this->face->glyph->bitmap;
	//		TextureData data;
	//		data.character = t;
	//		data.texture = new Texture();
	//		data.size = { (int)bitmap.width,(int)bitmap.rows };
	//		data.bearing = { face->glyph->bitmap_left,face->glyph->bitmap_top };
	//		data.texture->SetBuffer(bitmap.buffer, bitmap.width, bitmap.rows);
	//		data.texture->LoadShader("font");*/
	//		//this->datas.emplace_back(data);
	//	}
	//	++i;
	//}
//}
std::u32string Font::GetText() const
{
	return this->text;
}
void Font::SetSize(const unsigned int fontSize)
{
	this->size = fontSize;
}
unsigned int Font::GetSize() const
{
	return this->size;
}
std::map<char32_t,Font::TextureData>* Font::GetData()
{
	return &this->data;
}
void Font::Draw()
{
	OGF::Draw(this, &this->transform->position);
}