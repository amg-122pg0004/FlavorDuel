/*****************************************************************//**
 * \file   CardFactory.h
 * \brief  カードをデータからインスタンスを生成する
 * 
 * \author 土居将太郎
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