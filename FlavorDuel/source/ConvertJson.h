/*****************************************************************//**
 * \file   ConvertJson.h
 * \brief  Jsonと構造体をそれぞれに変換するクラス
 *
 * \author 土居将太郎
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

		/**
		 * \brief 文字コード5Cによる文字化け回避用
		 * \param text 処理前の文字列
		 * \return 処理後の文字列
		 */
		static std::string Escape0x5C(std::string text);
	};
}