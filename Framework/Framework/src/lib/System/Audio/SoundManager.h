
#pragma once
#include "Sound.h"
///Soundを管理するManager
class CSoundManager
{
public:
	explicit CSoundManager();				//コンストラクタ
	~CSoundManager();						//デストラクタ
	void SetMaxVolume(const float value_);	//最大音量を登録する
	float GetMaxVolume() const;				//最大音量を返す
	void SetVolume(const CSound* s,			//選択されたSoundの音量を最大音量に適応した値に変える
					const float value_);
	void SetSound(CSound* s);				//Soundデータを登録する
	bool DeleteSound(const CSound* s);	//Soundデータを破棄する
	void AllDelete();						//Soundデータを全削除する
	void Application();						//最大音量を登録されているSoundすべてに適応させる
private:
	float MaxVolume;						//最大音量を格納する
	std::vector<CSound*> sounddata;			//適応させるSoundのデータを格納する
};