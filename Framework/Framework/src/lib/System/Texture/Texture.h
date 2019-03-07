
#pragma once
#include "Shader\Shader.h"
/**
*@brief	‰æ‘œ‚Ì“Ç‚İ‚İ‚ğs‚¤class
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
};