/*****************************************************************//**
 * \file   CardFactory.h
 * \brief  カードをデータからインスタンスを生成する
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <memory>
#include <map>
#include "CardDataStruct.h"

namespace Flavor {
	class CardObject;
	class CardFactory {
	public:
		CardFactory();
		std::unique_ptr<CardObject> CreateCard(CardData data);
	private:
		std::map<int, std::string> _cardImageMap;
	};
}