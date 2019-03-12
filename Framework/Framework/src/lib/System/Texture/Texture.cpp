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
	shader = ResourceManager::Get()->GetShaderData("simple");
}
Texture::Texture(const std::string& path)
{
	glGenTextures(1, &this->id);
	shader = ResourceManager::Get()->GetShaderData("simple");
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
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}
bool Texture::Load(const cv::Mat& mat)
{
	glBindTexture(GL_TEXTURE_2D, this->id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mat.cols, mat.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, mat.ptr());
	size.x = mat.cols;
	size.y = mat.rows;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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