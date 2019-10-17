#pragma once
#include "System/System.h"
#include "Data.h"
#include "Texture\Texture.h"
#include "ResourceManager\ResourceManager.h"
#include "Engine\Framework.h"
#include "Font\Font.h"
#include "Sprite\Sprite.h"
#include "Window\Window.h"
#include "Scene\Scene.h"
/**
*@brief OpenGL Features
*/
class COGF
{
	static void Render(CTexture* texture, const GLfloat* vtx, const GLfloat* uv, const GLfloat* color)
	{
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		CShader* shader = texture->GetShader();
		shader->Use();

		COGF::SetAttrib(shader, "inpos", vtx, 2, GL_FLOAT, GL_FALSE);
		COGF::SetAttrib(shader, "inuv", uv, 2, GL_FLOAT, GL_FALSE);
		COGF::SetUniform1f(shader, "tex", 0);
		COGF::SetAttrib(shader, "incolor", color, 4, GL_FLOAT, GL_FALSE);
		COGF::SetUniformMat4f(shader, "viewMatrix", CFramework::Get()->GetScene()->GetCamera()->GetProjectionMatrix(), GL_FALSE);

		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	static void Render(CSprite* sprite, const GLfloat* vtx, const GLfloat* uv, const GLfloat* color)
	{
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		CShader* shader = sprite->texture->GetShader();
		shader->Use();

		COGF::SetAttrib(shader, "inpos", vtx, 2, GL_FLOAT, GL_FALSE);
		COGF::SetAttrib(shader, "inuv", uv, 2, GL_FLOAT, GL_FALSE);
		COGF::SetUniform1f(shader, "tex", 0);
		COGF::SetAttrib(shader, "incolor", color, 4, GL_FLOAT, GL_FALSE);
		COGF::SetUniformMat4f(shader, "viewMatrix", CFramework::Get()->GetScene()->GetCamera()->GetProjectionMatrix(), GL_FALSE);

		sprite->SetShaderData(shader);

		glBindTexture(GL_TEXTURE_2D, sprite->texture->GetID());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	static void Render(CShader* shader,const GLfloat* pos, const GLfloat* color)
	{
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		shader->Use();
		COGF::SetAttrib(shader, "inpos", pos, 2, GL_FLOAT, GL_FALSE);
		COGF::SetAttrib(shader, "incolor", color, 4, GL_FLOAT, GL_FALSE);
		GLfloat proj[16];
		CFramework::Get()->GetScene()->GetCamera()->ReverseProjectionMatrix(proj);
		COGF::SetUniformMat4f(shader, "viewMatrix", proj, GL_FALSE);

		glDrawArrays(GL_LINES, 0, 2);
	}
	static void Rotate(const float radian, GLfloat* matrix)
	{
		//ラジアンの値に変更
		float tora = KL::ToRadian(radian);
		//原点を指定
		CVec2 CEntry((*(matrix + 2) + *(matrix)) / 2, (*(matrix + 5) + *(matrix + 1)) / 2);
		//回転軸の原点の値を導く
		GLfloat v[]
		{
			*(matrix)-CEntry.x,*(matrix + 1) - CEntry.y,
			*(matrix + 2) - CEntry.x,*(matrix + 3) - CEntry.y,
			*(matrix + 4) - CEntry.x,*(matrix + 5) - CEntry.y,
			*(matrix + 6) - CEntry.x,*(matrix + 7) - CEntry.y,
		};
		//回転行列の生成
		GLfloat ma[4] = {
			cosf(tora),-sinf(tora),
			sinf(tora),cosf(tora),
		};
		//回転行列の計算
		*(matrix) = (*(v) * *(ma)) + (*(v + 1)* *(ma + 1));
		*(matrix + 1) = (*(v)* *(ma + 2)) + (*(v + 1)* *(ma + 3));

		*(matrix + 2) = (*(v + 2)* *(ma)) + (*(v + 3)* *(ma + 1));
		*(matrix + 3) = (*(v + 2)* *(ma + 2)) + (*(v + 3)* *(ma + 3));

		*(matrix + 4) = (*(v + 4)* *(ma)) + (*(v + 5)* *(ma + 1));
		*(matrix + 5) = (*(v + 4)* *(ma + 2)) + (*(v + 5)* *(ma + 3));

		*(matrix + 6) = (*(v + 6)* *(ma)) + (*(v + 7)* *(ma + 1));
		*(matrix + 7) = (*(v + 6)* *(ma + 2)) + (*(v + 7)* *(ma + 3));

		//回転軸の原点の移動した分を元に戻す
		*(matrix) = *(matrix)+CEntry.x;
		*(matrix + 1) = *(matrix + 1) + CEntry.y;

		*(matrix + 2) = *(matrix + 2) + CEntry.x;
		*(matrix + 3) = *(matrix + 3) + CEntry.y;

		*(matrix + 4) = *(matrix + 4) + CEntry.x;
		*(matrix + 5) = *(matrix + 5) + CEntry.y;

		*(matrix + 6) = *(matrix + 6) + CEntry.x;
		*(matrix + 7) = *(matrix + 7) + CEntry.y;
	}
	static CBox2D GetAbsolute(const CTransform* transform)
	{
		CBox2D draw(transform->position, transform->scale);
		draw.OffsetCEntrySize();
		return draw;
	}
public:
	static void Draw(CShader* shader, const CVec2& begin, const CVec2& end, const CColor& color)
	{
		Draw(shader, &begin, &end, &color);
	}
	static void Draw(CShader* shader, const CVec2* begin, const CVec2* end, const CColor* color)
	{
		GLfloat vtx[] = { begin->x,begin->y,end->x,end->y };
		GLfloat vcolor[] = {
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
		};
		Render(shader, vtx, vcolor);
	}
	static void Draw(CTexture* texture, const CTransform* transform)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(texture, &draw, 0.0f, &CColor::one);
	}
	static void Draw(CTexture* texture, const CTransform* transform, const float angle)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(texture, &draw, angle, &CColor::one);
	}
	static void Draw(CTexture* texture, const CTransform* transform, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(texture, &draw, 0.0f, color);
	}
	static void Draw(CTexture* texture, const CTransform* transform, const float angle, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(texture, &draw, angle, color);
	}
	static void Draw(CTexture* texture, const CTransform* transform, const CBox2D* src, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(texture, &draw, src, transform->angle, color);
	}
	static void Draw(CTexture* texture, const CTransform* draw, const CTransform* src)
	{
		CBox2D boxdraw = GetAbsolute(draw);
		CBox2D boxsrc = GetAbsolute(src);
		Draw(texture, &boxdraw, &boxsrc, draw->angle, &CColor::one);
	}
	static void Draw(CTexture* texture, const CTransform* draw, const CTransform* src, const CColor* color)
	{
		CBox2D boxdraw = GetAbsolute(draw);
		CBox2D boxsrc = GetAbsolute(src);
		Draw(texture, &boxdraw, &boxsrc, draw->angle, color);
	}
	static void Draw(CTexture* texture, const CBox2D* draw)
	{
		Draw(texture, draw, 0.0f, &CColor::one);
	}
	static void Draw(CTexture* texture, const CBox2D* draw, const float angle)
	{
		Draw(texture, draw, angle, &CColor::one);
	}
	static void Draw(CTexture* texture, const CBox2D* draw, const CColor* color)
	{
		Draw(texture, draw, 0.0f, color);
	}
	static void Draw(CTexture* texture, const CBox2D* draw, const float angle,const CColor* color)
	{
		GLfloat vtx[] = {
			draw->x,draw->h,
			draw->w,draw->h,
			draw->w,draw->y,
			draw->x,draw->y,
		};
		Rotate(angle, &vtx[0]);
		const GLfloat texuv[] = {
			0.f,1.f,
			1.f,1.f,
			1.f,0.f,
			0.f,0.f,
		};
		const GLfloat texcolor[] = {
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
		};
		Render(texture, vtx, texuv, texcolor);
	}
	static void Draw(CTexture* texture, const CBox2D* draw, const CBox2D* src)
	{
		Draw(texture, draw, src, 0.0f, &CColor::one);
	}
	static void Draw(CTexture* texture, const CBox2D* draw, const CBox2D* src, const float angle, const CColor* color)
	{
		GLfloat vtx[] = {
		draw->x,draw->h,
		draw->w,draw->h,
		draw->w,draw->y,
		draw->x,draw->y,
		};
		Rotate(angle, &vtx[0]);
		const GLfloat texuv[] = {
			src->x / texture->GetSize()->x,src->h / texture->GetSize()->y,
			src->w / texture->GetSize()->x,src->h / texture->GetSize()->y,
			src->w / texture->GetSize()->x,src->y / texture->GetSize()->y,
			src->x / texture->GetSize()->x,src->y / texture->GetSize()->y,
		};
		const GLfloat texcolor[] = {
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
		};
		Render(texture, vtx, texuv, texcolor);
	}
	static void Draw(CSprite* sprite, const CTransform* transform)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, 0.0f, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CTransform* transform, const float angle)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, angle, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CTransform* transform, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, 0.0f, color);
	}
	static void Draw(CSprite* sprite, const CTransform* transform, const float angle, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, angle, color);
	}
	static void Draw(CSprite* sprite, const CTransform* transform, const CBox2D* src, const CColor* color)
	{
		CBox2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, src, transform->angle, color);
	}
	static void Draw(CSprite* sprite, const CTransform* draw, const CTransform* src)
	{
		CBox2D boxdraw = GetAbsolute(draw);
		CBox2D boxsrc = GetAbsolute(src);
		Draw(sprite, &boxdraw, &boxsrc, draw->angle, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CTransform* draw, const CTransform* src, const CColor* color)
	{
		CBox2D boxdraw = GetAbsolute(draw);
		CBox2D boxsrc = GetAbsolute(src);
		Draw(sprite, &boxdraw, &boxsrc, draw->angle, color);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw)
	{
		Draw(sprite, draw, 0.0f, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw, const float angle)
	{
		Draw(sprite, draw, angle, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw, const CColor* color)
	{
		Draw(sprite, draw, 0.0f, color);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw, const float angle, const CColor* color)
	{
		GLfloat vtx[] = {
			draw->x,draw->h,
			draw->w,draw->h,
			draw->w,draw->y,
			draw->x,draw->y,
		};
		Rotate(angle, &vtx[0]);
		const GLfloat texuv[] = {
			0.f,1.f,
			1.f,1.f,
			1.f,0.f,
			0.f,0.f,
		};
		const GLfloat texcolor[] = {
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
		};
		Render(sprite, vtx, texuv, texcolor);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw, const CBox2D* src)
	{
		Draw(sprite, draw, src, 0.0f, &CColor::one);
	}
	static void Draw(CSprite* sprite, const CBox2D* draw, const CBox2D* src, const float angle, const CColor* color)
	{
		GLfloat vtx[] = {
		draw->x,draw->h,
		draw->w,draw->h,
		draw->w,draw->y,
		draw->x,draw->y,
		};
		Rotate(angle, &vtx[0]);
		const GLfloat texuv[] = {
			src->x / sprite->texture->GetSize()->x,src->h / sprite->texture->GetSize()->y,
			src->w / sprite->texture->GetSize()->x,src->h / sprite->texture->GetSize()->y,
			src->w / sprite->texture->GetSize()->x,src->y / sprite->texture->GetSize()->y,
			src->x / sprite->texture->GetSize()->x,src->y / sprite->texture->GetSize()->y,
		};
		const GLfloat texcolor[] = {
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
			color->red,
			color->green,
			color->blue,
			color->alpha,
		};
		Render(sprite, vtx, texuv, texcolor);
	}
	static void Draw(CFont* font, const CVec2* pos)
	{
		COGF::Draw(font, pos, &CColor::one);
	}
	static void Draw(CFont* font, const CVec2* pos, const CColor* color)
	{
		CVec2 offset;
		for (int i = 0;i < font->GetText().size();++i)
		{
			CFont::STextureData d = font->GetData()->at(font->GetText().at(i));
			float x = offset.x + pos->x;
			CBox2D draw(x, pos->y - (float)d.size.y, (float)d.size.x, (float)d.size.y);
			offset.x += d.size.x;
			draw.OffsetSize();
			COGF::Draw(d.texture, &draw, color);
		}
	}
	static void SetAttrib(CShader* shader, const std::string& name, const GLfloat* mat, const GLint& size, GLenum type, GLboolean flag)
	{
		GLuint id = shader->Attrib(name);
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, size, type, flag, 0, mat);
	}
	static void SetUniform1f(CShader* shader, const std::string& name,const GLfloat v0)
	{
		GLint id = shader->Uniform(name);
		glUniform1f(id, v0);
	}
	static void SetUniform2f(CShader* shader, const std::string& name, const GLfloat* mat)
	{
		GLuint id = shader->Uniform(name);
		glUniform2f(id, mat[0], mat[1]);
	}
	static void SetUniformMat4f(CShader* shader, const std::string& name, const GLfloat* mat, GLboolean normalize)
	{
		GLuint id = shader->Uniform(name);
		glUniformMatrix4fv(id, 1, normalize, mat);
	}
};