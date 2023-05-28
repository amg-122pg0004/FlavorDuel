/*****************************************************************//**
 * \file   CardFactory.h
 * \brief  �J�[�h���f�[�^����C���X�^���X�𐶐�����
 * 
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <memory>
#include "CardDataStruct.h"

namespace Flavor {
	class CardObject;
	class CardFactory {
	public:
		static std::unique_ptr<CardObject> CreateCard(CardData data);
	};
}