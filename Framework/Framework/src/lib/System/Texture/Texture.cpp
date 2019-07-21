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
	glGenTextures(1, &id);
	shader = ResourceManager::Get()->GetShaderData("simple");
}
Texture::Texture(const std::string& path)
{
	glGenTextures(1, &id);
	shader = ResourceManager::Get()->GetShaderData("simple");
	Load(path);
}
Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &id);
}
bool Texture::Load(const std::string& path)
{
	glBindTexture(GL_TEXTURE_2D, id);
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
	glBindTexture(GL_TEXTURE_2D, id);
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
	return id;
}
Vec2Int* Texture::GetSize()
{
	return &size;
}
void Texture::SetShader(Shader* addShader)
{
	shader = addShader;
}
bool Texture::LoadShader(const std::string& name)
{
	shader = ResourceManager::Get()->GetShaderData(name);
	return (shader != nullptr) ? true : false;
}
Shader* Texture::GetShader()
{
	return shader;
}
void Texture::SetBuffer(unsigned char* buffer, unsigned int w, unsigned int h)
{
	glBindTexture(GL_TEXTURE_2D, id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	size.Set((int)w, (int)h);
}
void Texture::GetPixels(const Texture * tex, Color * out)
{
	unsigned char* data = new unsigned char[tex->size.x*tex->size.y * 4];
	glBindTexture(GL_TEXTURE_2D, tex->id);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	for (int y = 0; y < tex->size.y; ++y)
	{
		for (int x = 0; x < tex->size.x; ++x)
		{
			out[(y * tex->size.x + x)].red   = data[4 * (y * tex->size.x + x) + 0];
			out[(y * tex->size.x + x)].green = data[4 * (y * tex->size.x + x) + 1];
			out[(y * tex->size.x + x)].blue  = data[4 * (y * tex->size.x + x) + 2];
			out[(y * tex->size.x + x)].alpha = data[4 * (y * tex->size.x + x) + 3];
		}
		printf("\n");
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
}
Color* Texture::NewPixels(const Texture* tex)
{
	return (Color*)malloc(tex->size.x * tex->size.y * sizeof(Color));
}
std::vector<std::vector<Color>> Texture::VectorFromArray(const Texture * tex, const Color * in)
{
	return VectorFromArray(tex, in, 0, 0, tex->size.x, tex->size.y);
}
std::vector<std::vector<Color>> Texture::VectorFromArray(const Texture * tex, const Color * in, int x, int y, int w, int h)
{
	std::vector<std::vector<Color>> result;
	result.resize(h);
	for (int i = 0; i < h; ++i)
	{
		result[i].resize(w);
	}
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			result[i][j] = in[(i + y) * tex->size.y + (j + x)];
		}
	}
	return result;
}
Color Texture::ColorFromArray(const Texture * tex, const Color * in, int x, int y)
{
	return Color(in[y * tex->size.y + x]);;
}
void Texture::FreePixels(Color* in)
{
	free(in);
}
#if ENGINE_DEBUG
void Texture::OutputPixcelData()
{
	printf("===OutputPixcelData===\n");
	unsigned char* data = new unsigned char[size.x*size.y * 4];
	glBindTexture(GL_TEXTURE_2D, id);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			printf("[%d:%d:%d:%d] "
				, data[4 * (y * size.x + x) + 0]
				, data[4 * (y * size.x + x) + 1]
				, data[4 * (y * size.x + x) + 2]
				, data[4 * (y * size.x + x) + 3]
			);
		}
		printf("\n");
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] data;
	printf("\n===End===\n");
}
#endif
