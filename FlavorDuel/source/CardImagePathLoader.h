/*****************************************************************//**
 * \file   CardImagePathLoader.h
 * \brief  �J�[�h�摜��ID����t�@�C���p�X���Ăяo����悤�ɓǂݍ���ł����N���X
 *         �J�[�h�摜ID�͉摜���ƂɘA�ԂŐݒ肵�����̂��f�[�^�x�[�X��ɂ���
 * 
 * \author �y�������Y
 * \date   June 2023
 *********************************************************************/
#pragma once
#include <map>
#include <string>
namespace Flavor {
	class CardImagePathLoader
	{
	public:
		CardImagePathLoader();
		std::string GetPath(int id);
	private:
		std::map<int, std::string> _cardImageMap;
	};
}
