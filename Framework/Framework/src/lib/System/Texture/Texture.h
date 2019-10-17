
#pragma once
#include "Shader\Shader.h"
#include "Engine\EngineMacro.h"
#include <vector>
/**
*@brief	âÊëúÇÃì«Ç›çûÇ›ÇçsÇ§class
*/
class CTexture
{
	GLuint id;
	CVec2Int size;
	int comp;
	CShader* shader;
public:
	explicit CTexture();
	explicit CTexture(const std::string& path);
	virtual ~CTexture();
	GLuint GetID() const;
	CVec2Int* GetSize();
	bool Load(const std::string& path);
	bool Load(const cv::Mat& mat);
	void SetShader(CShader* shader);
	bool LoadShader(const std::string& name);
	CShader* GetShader();
	void SetBuffer(unsigned char* buffer, unsigned int w, unsigned int h);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Texture Pixel

	static void GetPixels(const CTexture* tex, CColor* out);
	static CColor* NewPixels(const CTexture* tex);
	static std::vector<std::vector<CColor>> VectorFromArray(const CTexture* tex,const CColor* in);
	static std::vector<std::vector<CColor>> VectorFromArray(const CTexture* tex, const CColor* in, int x, int y, int w, int h);
	static CColor ColorFromArray(const CTexture* tex, const CColor* in, int x, int y);
	static void FreePixels(CColor* in);

	///////////////////////////////////////////////////////////////////////////////////////////////////////

#if ENGINE_DEBUG
	void OutputPixcelData();
#endif
};