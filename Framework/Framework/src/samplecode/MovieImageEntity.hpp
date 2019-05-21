#pragma once
#include "MovieImage\Video.h"
#include "Entity\Entity.h"

/**
*@file MovieImageEntity.hpp
*@brief MovieImage Sample Code 
*@author kanekona
*@data 2019/04/28
*@details MovieImage‚ð“Ç‚Ýž‚ñ‚ÅŽ©•ª‚ÌŽq‚É“o˜^‚·‚é
* íœ‚ÍŽ©“®‚Å‚³‚ê‚é‚Ì‚ÅAdelete‚ð‚µ–Y‚ê‚Ä‚à–â‘è‚Í‚È‚¢
*/

/**
*@namespace Sample
*§ìŽÒ‚ª‹Lq‚·‚éƒTƒ“ƒvƒ‹ƒR[ƒh
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
			//¶¬
			Video* movie = new Video;
			//“Ç‚Ýž‚Ý,MP4,WAV
			movie->Load("./data/not/videos/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
			//Žq‚É“o˜^‚·‚é
			SetChildren(movie);
		}
	public:
	};
}