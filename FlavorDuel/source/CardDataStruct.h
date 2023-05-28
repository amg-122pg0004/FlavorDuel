/*****************************************************************//**
 * \file  CardDataStruct.h
 * \brief カード、プレイヤーデータ、部屋データ　サーバー上で管理しているデータと同じ形の構造体
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "RoomState.h"
#include <string>
#include <vector>
namespace Flavor {
	enum class JudgeType {
		higherAttack,
		higherDefence,
		higherTotal,
		lowerAttack,
		lowerDefence,
		lowerTotal,
	};

	struct CardData {
		std::string name;
		std::string flavorText;
		int cg = -1;
		int attack = -1;
		int defence = -1;
	};
	struct PlayerData {
		std::string id;
		std::vector<CardData> deck;
		std::vector<CardData> hand;
		CardData battle;
		int win;
	};
	struct RoomData {
		PlayerData player1;
		PlayerData player2;
		JudgeType judgeType;
		RoomState state;
	};
}
