#pragma once
#include "System/System.h"
#include "Data.h"
#include "Texture\Texture.h"
#include "ResourceManager\ResourceManager.h"
#include "Engine\Framework.h"
#include "Font\Font.h"
/**
*@brief OpenGL Features
*/
class OGF
{
	static void Render(Texture* texture, const GLfloat* vtx, const GLfloat* uv, const GLfloat* color)
	{
//		glBindTexture(GL_TEXTURE_2D,texture->GetID());
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		Shader* shader = texture->GetShader();
		shader->Use();
		GLint in_posLocation = shader->Attrib("inpos");
		GLint in_uvLocation = shader->Attrib("inuv");
		GLint in_texture = shader->Uniform("tex");
		GLuint in_color = shader->Attrib("incolor");
		GLuint in_proj = shader->Uniform("viewMatrix");

		//GLuint in_screen = shader->Attrib("inscreen");
		//GLuint in_scale = shader->Attrib("inscale");

		glEnableVertexAttribArray(in_posLocation);
		glEnableVertexAttribArray(in_uvLocation);
		glEnableVertexAttribArray(in_color);

		glUniform1f(in_texture, 0);
		glUniformMatrix4fv(in_proj, 1, GL_FALSE, Framework::Get()->GetScene()->GetCamera()->GetProjectionMatrix());

		glVertexAttribPointer(in_posLocation, 2, GL_FLOAT, GL_FALSE, 0, vtx);
		glVertexAttribPointer(in_uvLocation, 2, GL_FLOAT, GL_FALSE, 0, uv);
		glVertexAttribPointer(in_color, 4, GL_FLOAT, GL_FALSE, 0, color);
//		glVertexAttribPointer(in_screen, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	static void Rotate(const float radian, GLfloat* matrix)
	{
		//ラジアンの値に変更
		float tora = KL::ToRadian(radian);
		//原点を指定
		Vec2 Center((*(matrix + 2) + *(matrix)) / 2, (*(matrix + 5) + *(matrix + 1)) / 2);
		//回転軸の原点の値を導く
		GLfloat v[]
		{
			*(matrix)-Center.x,*(matrix + 1) - Center.y,
			*(matrix + 2) - Center.x,*(matrix + 3) - Center.y,
			*(matrix + 4) - Center.x,*(matrix + 5) - Center.y,
			*(matrix + 6) - Center.x,*(matrix + 7) - Center.y,
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
		*(matrix) = *(matrix)+Center.x;
		*(matrix + 1) = *(matrix + 1) + Center.y;

		*(matrix + 2) = *(matrix + 2) + Center.x;
		*(matrix + 3) = *(matrix + 3) + Center.y;

		*(matrix + 4) = *(matrix + 4) + Center.x;
		*(matrix + 5) = *(matrix + 5) + Center.y;

		*(matrix + 6) = *(matrix + 6) + Center.x;
		*(matrix + 7) = *(matrix + 7) + Center.y;
	}
	static Box2D GetAbsolute(const Transform* transform)
	{
		Box2D draw(transform->position, transform->scale);
		draw.OffsetCenterSize();
		return draw;
	}
public:
	static void Draw(Texture* texture, const Transform* transform)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(texture, &draw, 0.0f, &Color::one);
	}
	static void Draw(Texture* texture, const Transform* transform, const float angle)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(texture, &draw, angle, &Color::one);
	}
	static void Draw(Texture* texture, const Transform* transform, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(texture, &draw, 0.0f, color);
	}
	static void Draw(Texture* texture, const Transform* transform, const float angle, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(texture, &draw, angle, color);
	}
	static void Draw(Texture* texture, const Transform* transform, const Box2D* src, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(texture, &draw, src, transform->angle, color);
	}
	static void Draw(Texture* texture, const Transform* draw, const Transform* src)
	{
		Box2D boxdraw = GetAbsolute(draw);
		Box2D boxsrc = GetAbsolute(src);
		Draw(texture, &boxdraw, &boxsrc, draw->angle, &Color::one);
	}
	static void Draw(Texture* texture, const Transform* draw, const Transform* src, const Color* color)
	{
		Box2D boxdraw = GetAbsolute(draw);
		Box2D boxsrc = GetAbsolute(src);
		Draw(texture, &boxdraw, &boxsrc, draw->angle, color);
	}
	static void Draw(Texture* texture, const Box2D* draw)
	{
		Draw(texture, draw, 0.0f, &Color::one);
	}
	static void Draw(Texture* texture, const Box2D* draw, const float angle)
	{
		Draw(texture, draw, angle, &Color::one);
	}
	static void Draw(Texture* texture, const Box2D* draw, const Color* color)
	{
		Draw(texture, draw, 0.0f, color);
	}
	static void Draw(Texture* texture, const Box2D* draw, const float angle,const Color* color)
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
	static void Draw(Texture* texture, const Box2D* draw, const Box2D* src)
	{
		Draw(texture, draw, src, 0.0f, &Color::one);
	}
	static void Draw(Texture* texture, const Box2D* draw, const Box2D* src, const float angle, const Color* color)
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
	static void Draw(Font* font, const Vec2* pos)
	{
		OGF::Draw(font, pos, &Color::one);
	}
	static void Draw(Font* font, const Vec2* pos, const Color* color)
	{
		Vec2 offset;
		for (int i = 0;i < font->GetText().size();++i)
		{
			Font::TextureData d = font->GetData()->at(font->GetText().at(i));
			float x = offset.x + pos->x;
			Box2D draw(x, pos->y - (float)d.size.y, (float)d.size.x, (float)d.size.y);
			offset.x += d.size.x;
			draw.OffsetSize();
			OGF::Draw(d.texture, &draw, color);
		}
	}
};