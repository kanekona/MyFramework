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
class OGF
{
	static void Render(Texture* texture, const GLfloat* vtx, const GLfloat* uv, const GLfloat* color)
	{
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		Shader* shader = texture->GetShader();
		shader->Use();

		OGF::SetAttrib(shader, "inpos", vtx, 2, GL_FLOAT, GL_FALSE);
		OGF::SetAttrib(shader, "inuv", uv, 2, GL_FLOAT, GL_FALSE);
		OGF::SetUniform1f(shader, "tex", 0);
		OGF::SetAttrib(shader, "incolor", color, 4, GL_FLOAT, GL_FALSE);
		OGF::SetUniformMat4f(shader, "viewMatrix", Framework::Get()->GetScene()->GetCamera()->GetProjectionMatrix(), GL_FALSE);

		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	static void Render(Sprite* sprite, const GLfloat* vtx, const GLfloat* uv, const GLfloat* color)
	{
		glAlphaFunc(GL_GREATER, (GLclampf)0.0);
		Shader* shader = sprite->texture->GetShader();
		shader->Use();

		OGF::SetAttrib(shader, "inpos", vtx, 2, GL_FLOAT, GL_FALSE);
		OGF::SetAttrib(shader, "inuv", uv, 2, GL_FLOAT, GL_FALSE);
		OGF::SetUniform1f(shader, "tex", 0);
		OGF::SetAttrib(shader, "incolor", color, 4, GL_FLOAT, GL_FALSE);
		OGF::SetUniformMat4f(shader, "viewMatrix", Framework::Get()->GetScene()->GetCamera()->GetProjectionMatrix(), GL_FALSE);

		sprite->SetShaderData(shader);

		glBindTexture(GL_TEXTURE_2D, sprite->texture->GetID());
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindTexture(GL_TEXTURE_2D, 0);
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
	static void Draw(Sprite* sprite, const Transform* transform)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, 0.0f, &Color::one);
	}
	static void Draw(Sprite* sprite, const Transform* transform, const float angle)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, angle, &Color::one);
	}
	static void Draw(Sprite* sprite, const Transform* transform, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, 0.0f, color);
	}
	static void Draw(Sprite* sprite, const Transform* transform, const float angle, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, angle, color);
	}
	static void Draw(Sprite* sprite, const Transform* transform, const Box2D* src, const Color* color)
	{
		Box2D draw = GetAbsolute(transform);
		Draw(sprite, &draw, src, transform->angle, color);
	}
	static void Draw(Sprite* sprite, const Transform* draw, const Transform* src)
	{
		Box2D boxdraw = GetAbsolute(draw);
		Box2D boxsrc = GetAbsolute(src);
		Draw(sprite, &boxdraw, &boxsrc, draw->angle, &Color::one);
	}
	static void Draw(Sprite* sprite, const Transform* draw, const Transform* src, const Color* color)
	{
		Box2D boxdraw = GetAbsolute(draw);
		Box2D boxsrc = GetAbsolute(src);
		Draw(sprite, &boxdraw, &boxsrc, draw->angle, color);
	}
	static void Draw(Sprite* sprite, const Box2D* draw)
	{
		Draw(sprite, draw, 0.0f, &Color::one);
	}
	static void Draw(Sprite* sprite, const Box2D* draw, const float angle)
	{
		Draw(sprite, draw, angle, &Color::one);
	}
	static void Draw(Sprite* sprite, const Box2D* draw, const Color* color)
	{
		Draw(sprite, draw, 0.0f, color);
	}
	static void Draw(Sprite* sprite, const Box2D* draw, const float angle, const Color* color)
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
	static void Draw(Sprite* sprite, const Box2D* draw, const Box2D* src)
	{
		Draw(sprite, draw, src, 0.0f, &Color::one);
	}
	static void Draw(Sprite* sprite, const Box2D* draw, const Box2D* src, const float angle, const Color* color)
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
	static void SetAttrib(Shader* shader, const std::string& name, const GLfloat* mat, const GLint& size, GLenum type, GLboolean flag)
	{
		GLuint id = shader->Attrib(name);
		glEnableVertexAttribArray(id);
		glVertexAttribPointer(id, size, type, flag, 0, mat);
	}
	static void SetUniform1f(Shader* shader, const std::string& name,const GLfloat v0)
	{
		GLint id = shader->Uniform(name);
		glUniform1f(id, v0);
	}
	static void SetUniform2f(Shader* shader, const std::string& name, const GLfloat* mat)
	{
		GLuint id = shader->Uniform(name);
		glUniform2f(id, mat[0], mat[1]);
	}
	static void SetUniformMat4f(Shader* shader, const std::string& name, const GLfloat* mat, GLboolean normalize)
	{
		GLuint id = shader->Uniform(name);
		glUniformMatrix4fv(id, 1, normalize, mat);
	}
};