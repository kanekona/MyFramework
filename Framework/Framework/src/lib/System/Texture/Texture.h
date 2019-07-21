
#pragma once
#include "Shader\Shader.h"
#include "Engine\EngineMacro.h"
#include <vector>
/**
*@brief	âÊëúÇÃì«Ç›çûÇ›ÇçsÇ§class
*/
class Texture
{
	GLuint id;
	Vec2Int size;
	int comp;
	Shader* shader;
public:
	explicit Texture();
	explicit Texture(const std::string& path);
	virtual ~Texture();
	GLuint GetID() const;
	Vec2Int* GetSize();
	bool Load(const std::string& path);
	bool Load(const cv::Mat& mat);
	void SetShader(Shader* shader);
	bool LoadShader(const std::string& name);
	Shader* GetShader();
	void SetBuffer(unsigned char* buffer, unsigned int w, unsigned int h);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Texture Pixel

	static void GetPixels(const Texture* tex, Color* out);
	static Color* NewPixels(const Texture* tex);
	static std::vector<std::vector<Color>> VectorFromArray(const Texture* tex,const Color* in);
	static std::vector<std::vector<Color>> VectorFromArray(const Texture* tex, const Color* in, int x, int y, int w, int h);
	static Color ColorFromArray(const Texture* tex, const Color* in, int x, int y);
	static void FreePixels(Color* in);

	///////////////////////////////////////////////////////////////////////////////////////////////////////

#if ENGINE_DEBUG
	void OutputPixcelData();
#endif
};