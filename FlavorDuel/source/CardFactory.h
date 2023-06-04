/*****************************************************************//**
 * \file   CardFactory.h
 * \brief  �J�[�h�f�[�^����`��\�ȃC���X�^���X�𐶐�����
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <memory>
#include "CardDataStruct.h"
#include "CardImagePathLoader.h"

namespace Flavor {
	class CardObject;
	class CardImagePathLoader;
	class CardFactory {
	public:
		CardFactory();
		std::unique_ptr<CardObject> CreateCard(CardData data);
		std::unique_ptr<CardImagePathLoader>& GetCardImagePathLoader() { return _pathLoader; }
	private:
		std::unique_ptr<CardImagePathLoader> _pathLoader;
	};
}