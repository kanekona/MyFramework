#pragma once
#include "MovieImage\Video.h"
#include "Entity\Entity.h"

/**
*@file MovieImageEntity.hpp
*@brief MovieImage Sample Code 
*@author kanekona
*@data 2019/04/28
*@details MovieImageを読み込んで自分の子に登録する
* 削除は自動でされるので、deleteをし忘れても問題はない
*/

/**
*@namespace Sample
*制作者が記述するサンプルコード
*/
namespace Sample
{
	class MovieImageEntity : public Entity
	{
		void Update() override
		{

		}
		void Enter() override
		{
			//生成
			Video* movie = new Video;
			//読み込み,MP4,WAV
			movie->Load("./data/not/videos/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
			//子に登録する
			SetChildren(movie);
		}
	public:
	};
}