#pragma once
#include "MovieImage\MovieImage.h"
#include "Entity\Entity.h"

/**
*@file MovieImageEntity.hpp
*@brief MovieImage Sample Code 
*@author kanekona
*@data 2019/04/28
*@details MovieImage��ǂݍ���Ŏ����̎q�ɓo�^����
* �폜�͎����ł����̂ŁAdelete�����Y��Ă����͂Ȃ�
*/

/**
*@namespace Sample
*����҂��L�q����T���v���R�[�h
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
			//����
			MovieImage* movie = new MovieImage;
			//�ǂݍ���,MP4,WAV
			movie->Load("./data/not/videos/TestMovie", MovieFormat::MP4, MovieFormat::WAV);
			//�q�ɓo�^����
			SetChildren(movie);
		}
	public:
	};
}