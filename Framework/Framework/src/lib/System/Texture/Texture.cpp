#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ResourceManager\ResourceManager.h"
#include "Engine\Framework.h"
//--------------------------------------------------
//@:Textureclass									
//--------------------------------------------------
Texture::Texture()
{
	glGenTextures(1, &this->id);
}
Texture::Texture(const std::string& path)
{
	glGenTextures(1, &this->id);
	Load(path);
}
Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &this->id);
}
bool Texture::Load(const std::string& path)
{
	glBindTexture(GL_TEXTURE_2D, this->id);
	unsigned char* data = stbi_load(path.c_str(), &size.x, &size.y, &comp, 0);
	if (data == NULL)
	{
		return false;
	}
	GLint type = (comp == 3) ? GL_RGB : GL_RGBA;
	//画像データをOpenGLへ送る
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, type, size.x, size.y, 0, type, GL_UNSIGNED_BYTE, data);
	//元データの破棄
	stbi_image_free(data);
	//表示用設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	shader = ResourceManager::Get()->GetShaderData("simple");
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
bool Texture::Load(const cv::Mat& mat)
{
	glBindTexture(GL_TEXTURE_2D, this->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mat.cols, mat.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, mat.ptr());
	size.x = mat.cols;
	size.y = mat.rows;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	shader = ResourceManager::Get()->GetShaderData("simple");
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
GLuint Texture::GetID() const
{
	return this->id;
}
Vec2Int* Texture::GetSize()
{
	return &this->size;
}
void Texture::SetShader(Shader* addShader)
{
	this->shader = addShader;
}
bool Texture::LoadShader(const std::string& name)
{
	this->shader = ResourceManager::Get()->GetShaderData(name);
	return (shader != nullptr) ? true : false;
}
Shader* Texture::GetShader()
{
	return this->shader;
}
void Texture::SetBuffer(unsigned char* buffer, unsigned int w, unsigned int h)
{
	glBindTexture(GL_TEXTURE_2D, this->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	this->size.Set((int)w, (int)h);
}
//!Test
void Texture::Draw(Box2D* draw)
{
	GLfloat vtx[] = {
		draw->x,draw->h,
		draw->w,draw->h,
		draw->w,draw->y,
		draw->x,draw->y,
	};
	const GLfloat texuv[] = {
		1.f,1.f,
		1.f,1.f,
		1.f,1.f,
		1.f,1.f,
	};
	const GLfloat texcolor[] = {
		1.f,1.f,1.f,1.f,
		1.f,1.f,1.f,1.f,
		1.f,1.f,1.f,1.f,
		1.f,1.f,1.f,1.f
	};
	glAlphaFunc(GL_GREATER, (GLclampf)0.0);
	{
		shader->Use();
		GLint in_posLocation = shader->Attrib("inpos");
		GLint in_uvLocation = shader->Attrib("inuv");
		GLint in_texture = shader->Uniform("tex");
		GLuint in_color = shader->Attrib("incolor");
		GLuint in_proj = shader->Uniform("viewMatrix");

		glEnableVertexAttribArray(in_posLocation);
		glEnableVertexAttribArray(in_uvLocation);
		glEnableVertexAttribArray(in_color);

		glUniform1f(in_texture, 0);
		glUniformMatrix4fv(in_proj, 1, GL_FALSE, Framework::Get()->GetScene()->GetCamera()->GetProjectionMatrix());

		glVertexAttribPointer(in_posLocation, 2, GL_FLOAT, GL_FALSE, 0, vtx);
		glVertexAttribPointer(in_uvLocation, 2, GL_FLOAT, GL_FALSE, 0, texuv);
		glVertexAttribPointer(in_color, 4, GL_FLOAT, GL_FALSE, 0, texcolor);

		glBindTexture(GL_TEXTURE_2D, id);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	}
	{
	/*	glBindTexture(GL_TEXTURE_2D, id);
		glVertexPointer(2, GL_FLOAT, 0, vtx);
		glTexCoordPointer(2, GL_FLOAT, 0, texuv);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glEnable(GL_ALPHA_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDrawArrays(GL_QUADS, 0, 4);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_ALPHA_TEST);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, 0);*/
	}
}