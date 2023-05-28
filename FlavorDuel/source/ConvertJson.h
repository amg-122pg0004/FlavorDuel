/*****************************************************************//**
 * \file   ConvertJson.h
 * \brief  Json�ƍ\���̂����ꂼ��ɕϊ�����N���X
 *
 * \author �y�������Y
 * \date   May 2023
 *********************************************************************/
#pragma once
#include <picojson.h>
#include "CardDataStruct.h"
namespace Flavor {
	class ConvertJson
	{
	public:

		static picojson::object CardDataToJson(CardData data);
		static CardData JsonToCardData(picojson::object json);

		static picojson::array DeckDataToJson(std::vector<CardData> data);
		static std::vector<CardData> JsonToDeckData(picojson::array json);

		static picojson::object PlayerDataToJson(PlayerData playerData);
		static PlayerData JsonToPlayerData(picojson::object json);

		static picojson::object RoomDataToJson(RoomData roomData);
		static RoomData JsonToRoomData(picojson::object json);
	};
}