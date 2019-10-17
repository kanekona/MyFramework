#include "Font.h"
#include "Engine\OGF.hpp"

CFont::CFont()
	:CSprite(CSprite::REGISTERD_CANVAS)
{
	FT_Init_FreeType(&ft_library);
	if (!ft_library)
	{
#ifdef KL_DEBUG
		std::cout << "FontInitError" << std::endl;
#endif
		return;
	}
	FT_New_Face(ft_library, "data/font/msgothic.ttc", 0, &face);
	size = 8.0f;
}
CFont::~CFont()
{
	for (auto& it : data)
	{
		delete it.second.texture;
	}
	data.clear();
	FT_Done_Face(face);
	FT_Done_FreeType(ft_library);
}
void CFont::SetText(const std::wstring& t)
{
	text = t;
	for (auto c : text)
	{
		if (data.count(c) == 0)
		{
			FT_Set_Pixel_Sizes(face, size, size);
			FT_Get_Char_Index(face, c);
			FT_Load_Char(face, c, FT_LOAD_RENDER);
			FT_Render_Glyph(face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);

			FT_Bitmap bitmap = face->glyph->bitmap;
			STextureData d;
			d.character = c;
			d.texture = new CTexture();
			d.size = { (int)bitmap.width,(int)bitmap.rows };
			d.bearing = { face->glyph->bitmap_left,face->glyph->bitmap_top };
			d.texture->SetBuffer(bitmap.buffer, bitmap.width, bitmap.rows);
			d.texture->LoadShader("font");
			data.insert(std::make_pair(c,d));
		}
	}
}
//void Font::SetText(const std::string& t,unsigned int* offset)
//{
	//text = t;
	//unsigned int i = 0;
	//for (auto c : text)
	//{
	//	//ƒf[ƒ^‚É‚È‚¢•¶Žš‚È‚ç’Ç‰Á‚·‚é
	//	//if (Check(t))
	//	{
	//		/*FT_Set_Pixel_Sizes(face, size + offset[i], size + offset[i]);
	//		FT_Get_Char_Index(face, t);
	//		FT_Load_Char(face, t, FT_LOAD_RENDER);
	//		FT_Render_Glyph(face->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);

	//		FT_Bitmap bitmap = face->glyph->bitmap;
	//		TextureData data;
	//		data.character = t;
	//		data.texture = new Texture();
	//		data.size = { (int)bitmap.width,(int)bitmap.rows };
	//		data.bearing = { face->glyph->bitmap_left,face->glyph->bitmap_top };
	//		data.texture->SetBuffer(bitmap.buffer, bitmap.width, bitmap.rows);
	//		data.texture->LoadShader("font");*/
	//		//datas.emplace_back(data);
	//	}
	//	++i;
	//}
//}
std::wstring CFont::GetText() const
{
	return text;
}
void CFont::SetSize(const unsigned int fontSize)
{
	size = fontSize;
}
unsigned int CFont::GetSize() const
{
	return size;
}
std::map<wchar_t,CFont::STextureData>* CFont::GetData()
{
	return &data;
}
void CFont::Draw()
{
	COGF::Draw(this, &transform->position);
}