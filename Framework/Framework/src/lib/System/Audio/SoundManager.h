
#pragma once
#include "Sound.h"
///Sound���Ǘ�����Manager
class CSoundManager
{
public:
	explicit CSoundManager();				//�R���X�g���N�^
	~CSoundManager();						//�f�X�g���N�^
	void SetMaxVolume(const float value_);	//�ő剹�ʂ�o�^����
	float GetMaxVolume() const;				//�ő剹�ʂ�Ԃ�
	void SetVolume(const CSound* s,			//�I�����ꂽSound�̉��ʂ��ő剹�ʂɓK�������l�ɕς���
					const float value_);
	void SetSound(CSound* s);				//Sound�f�[�^��o�^����
	bool DeleteSound(const CSound* s);	//Sound�f�[�^��j������
	void AllDelete();						//Sound�f�[�^��S�폜����
	void Application();						//�ő剹�ʂ�o�^����Ă���Sound���ׂĂɓK��������
private:
	float MaxVolume;						//�ő剹�ʂ��i�[����
	std::vector<CSound*> sounddata;			//�K��������Sound�̃f�[�^���i�[����
};