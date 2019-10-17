
#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <string>
#include <vector>

class CSound;
class CTexture;
class CShader;

/**
*@brief	リソースを生成、解放、管理を行うclass
*
*既存GameEngineを使用している場合は自動で生成される
*
*ここに登録しているものはEngine終了時自動でdeleteされるので自分でdeleteしないこと
*
*newせず登録したものは自分でDeleteResource呼んで消しておくこと
*/
class CResourceManager : private CNonCopyable
{
	//! サウンドデータ
	std::vector<std::pair<std::string, CSound*>> soundData;
	//! テクスチャデータ
	std::vector<std::pair<std::string, CTexture*>> textureData;
	//! シェーダーデータ
	std::vector<std::pair<std::string, CShader*>> shaderData;
	//! Singleton
	static CResourceManager* instance;
public:
	/**
	*@brief	存在するサウンドデータのポインタを登録する
	*@param[in] string name 登録名
	*@param[in]	Sound* sound サウンドデータのポインタ
	*/
	void SetSoundData(const std::string& name,CSound* sound);
	/**
	*@brief	新しくサウンドを生成しデータに登録する
	*@param[in] string name 登録名
	*@param[in]	string path ファイルのパス
	*@return bool 生成に成功でtrueを返す
	*/
	bool CreateSound(const std::string& name, const std::string& path);
	/**
	*@brief	登録されているサウンドデータを返す
	*@param[in] string name　登録名
	*@return Sound* 登録されているサウンドを返す
	*/
	CSound* GetSoundData(const std::string& name);
	/**
	*@brief	存在するテクスチャデータのポインタを登録する
	*@param[in]	string 登録名
	*@param[in]	Texture* tex テクスチャデータのポインタ
	*/
	void SetTextureData(const std::string& name,CTexture* tex);
	/**
	*@brief	新しくテクスチャを生成しデータを登録する
	*@param[in]	string name 登録名
	*@param[in]	string path ファイルのパス
	*@return bool 生成に成功でtrueを返す
	*/
	bool CreateTexture(const std::string& name, const std::string& path);
	/**
	*@brief	登録されているテクスチャデータを返す
	*@param[in] string name 登録名
	*@return Sound* 登録されているテクスチャを返す
	*/
	CTexture* GetTextureData(const std::string& name);
	/**
	*@brief	登録されているテクスチャデータを破棄,deleteする
	*@param[in]	string name 登録名
	*@return bool 削除に成功でtrue
	*/
	bool DeleteTexture(const std::string& name);
	/**
	*@brief	登録されているサウンドデータを破棄,deleteする
	*@param[in]	string name 登録名
	*@return bool 削除に成功でtrue
	*/
	bool DeleteSound(const std::string& name);
	/**
	*@brief	新しくシェーダーを生成しデータを登録する
	*@param[in] const string& name 登録名
	*@param[in] const string& path ファイルパス
	*@return bool 生成に成功でtrueを返す
	*/
	bool CreateShader(const std::string& name, const std::string& path);
	/**
	*@brief	登録されているシェーダーデータを取得する
	*@param[in] const string& name 登録名
	*@return Shader* 登録されているシェーダーデータ
	*/
	CShader* GetShaderData(const std::string& name);
	/**
	*@brief	destructor 
	*全データを破棄,deleteする
	*/
	virtual ~CResourceManager();
	/**
	*@brief	Create Singleton Instance
	*@return ResourceManager* instance
	*/
	static CResourceManager* Create();
	/**
	*@brief	Get Instance
	*@return ResourceManager* instance
	*/
	static CResourceManager* Get();
	/**
	*@brief	Destroy Instance
	*/
	static void Destroy();
};
//ResourceManager* ResourceManager::instance = nullptr;