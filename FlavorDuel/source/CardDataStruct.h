/*****************************************************************//**
 * \file   CardDataStruct.h
 * \brief  カードデータおよびデッキデータ型
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <string>
#include <vector>
namespace Flavor {
	struct CardData
	{
		std::string name;
		std::string flavorText;
		int image;
	};

	struct DeckData
	{
		std::string name;
		std::vector<CardData> cards;
	};
}
