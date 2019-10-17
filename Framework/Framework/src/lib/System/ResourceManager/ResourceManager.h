
#pragma once
#include "NonCopyable\NonCopyable.hpp"
#include <string>
#include <vector>

class CSound;
class CTexture;
class CShader;

/**
*@brief	���\�[�X�𐶐��A����A�Ǘ����s��class
*
*����GameEngine���g�p���Ă���ꍇ�͎����Ő��������
*
*�����ɓo�^���Ă�����̂�Engine�I����������delete�����̂Ŏ�����delete���Ȃ�����
*
*new�����o�^�������͎̂�����DeleteResource�Ă�ŏ����Ă�������
*/
class CResourceManager : private CNonCopyable
{
	//! �T�E���h�f�[�^
	std::vector<std::pair<std::string, CSound*>> soundData;
	//! �e�N�X�`���f�[�^
	std::vector<std::pair<std::string, CTexture*>> textureData;
	//! �V�F�[�_�[�f�[�^
	std::vector<std::pair<std::string, CShader*>> shaderData;
	//! Singleton
	static CResourceManager* instance;
public:
	/**
	*@brief	���݂���T�E���h�f�[�^�̃|�C���^��o�^����
	*@param[in] string name �o�^��
	*@param[in]	Sound* sound �T�E���h�f�[�^�̃|�C���^
	*/
	void SetSoundData(const std::string& name,CSound* sound);
	/**
	*@brief	�V�����T�E���h�𐶐����f�[�^�ɓo�^����
	*@param[in] string name �o�^��
	*@param[in]	string path �t�@�C���̃p�X
	*@return bool �����ɐ�����true��Ԃ�
	*/
	bool CreateSound(const std::string& name, const std::string& path);
	/**
	*@brief	�o�^����Ă���T�E���h�f�[�^��Ԃ�
	*@param[in] string name�@�o�^��
	*@return Sound* �o�^����Ă���T�E���h��Ԃ�
	*/
	CSound* GetSoundData(const std::string& name);
	/**
	*@brief	���݂���e�N�X�`���f�[�^�̃|�C���^��o�^����
	*@param[in]	string �o�^��
	*@param[in]	Texture* tex �e�N�X�`���f�[�^�̃|�C���^
	*/
	void SetTextureData(const std::string& name,CTexture* tex);
	/**
	*@brief	�V�����e�N�X�`���𐶐����f�[�^��o�^����
	*@param[in]	string name �o�^��
	*@param[in]	string path �t�@�C���̃p�X
	*@return bool �����ɐ�����true��Ԃ�
	*/
	bool CreateTexture(const std::string& name, const std::string& path);
	/**
	*@brief	�o�^����Ă���e�N�X�`���f�[�^��Ԃ�
	*@param[in] string name �o�^��
	*@return Sound* �o�^����Ă���e�N�X�`����Ԃ�
	*/
	CTexture* GetTextureData(const std::string& name);
	/**
	*@brief	�o�^����Ă���e�N�X�`���f�[�^��j��,delete����
	*@param[in]	string name �o�^��
	*@return bool �폜�ɐ�����true
	*/
	bool DeleteTexture(const std::string& name);
	/**
	*@brief	�o�^����Ă���T�E���h�f�[�^��j��,delete����
	*@param[in]	string name �o�^��
	*@return bool �폜�ɐ�����true
	*/
	bool DeleteSound(const std::string& name);
	/**
	*@brief	�V�����V�F�[�_�[�𐶐����f�[�^��o�^����
	*@param[in] const string& name �o�^��
	*@param[in] const string& path �t�@�C���p�X
	*@return bool �����ɐ�����true��Ԃ�
	*/
	bool CreateShader(const std::string& name, const std::string& path);
	/**
	*@brief	�o�^����Ă���V�F�[�_�[�f�[�^���擾����
	*@param[in] const string& name �o�^��
	*@return Shader* �o�^����Ă���V�F�[�_�[�f�[�^
	*/
	CShader* GetShaderData(const std::string& name);
	/**
	*@brief	destructor 
	*�S�f�[�^��j��,delete����
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