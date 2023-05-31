#include "ConvertJson.h"
#include "appframe.h"
using namespace Flavor;

picojson::object Flavor::ConvertJson::CardDataToJson(CardData data)
{
	picojson::object result;

	std::string nameutf8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8((data.name));
	std::string textutf8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8((data.flavorText));
	result.insert(std::make_pair("name", picojson::value(nameutf8)));
	result.insert(std::make_pair("flavortext", picojson::value(textutf8)));
	result.insert(std::make_pair("cg", picojson::value(static_cast<double>(data.cg))));
	result.insert(std::make_pair("attack", picojson::value(static_cast<double>(data.attack))));
	result.insert(std::make_pair("defence", picojson::value(static_cast<double>(data.defence))));

	return result;
}

CardData Flavor::ConvertJson::JsonToCardData(picojson::object json)
{
	CardData result;

	auto wideName = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(json["name"].get<std::string>());
	auto shiftJisName = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wideName);
	auto wideText = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(json["flavortext"].get<std::string>());
	auto shiftJisText = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wideText);
	result.name = shiftJisName;
	result.flavorText = shiftJisText;
	result.cg = static_cast<int>(json["cg"].get<double>());
	result.attack = static_cast<int>(json["attack"].get<double>());
	result.defence = static_cast<int>(json["defence"].get<double>());

	return result;
}

picojson::array ConvertJson::DeckDataToJson(std::vector<CardData> data)
{
	picojson::array cardArray;
	for (auto&& card : data) {
		cardArray.emplace_back(CardDataToJson(card));
	}

	return cardArray;
}

std::vector<CardData> ConvertJson::JsonToDeckData(picojson::array json)
{
	std::vector<CardData> result;

	for (int i = 0; i < json.size(); ++i) {
		picojson::object object = json[i].get<picojson::object>();
		CardData cardData = JsonToCardData(object);
		result.emplace_back(cardData);
	}

	return result;
}

picojson::object Flavor::ConvertJson::PlayerDataToJson(PlayerData playerData)
{
	picojson::object result;

	result.insert(std::make_pair("deck", DeckDataToJson(playerData.deck)));
	result.insert(std::make_pair("hand", DeckDataToJson(playerData.hand)));
	result.insert(std::make_pair("battle", CardDataToJson(playerData.battle)));
	result.insert(std::make_pair("oldBattle", CardDataToJson(playerData.oldBattle)));
	result.insert(std::make_pair("id", picojson::value(playerData.id)));
	result.insert(std::make_pair("win", picojson::value(static_cast<double>(playerData.win))));

	return result;
}

PlayerData Flavor::ConvertJson::JsonToPlayerData(picojson::object json)
{
	PlayerData result;

	if (json["deck"].is<picojson::array>()) {
		result.deck = JsonToDeckData(json["deck"].get<picojson::array>());
	}
	if (json["hand"].is<picojson::array>()) {
		result.hand = JsonToDeckData(json["hand"].get<picojson::array>());
	}
	if (json["battle"].is<picojson::object>()) {
		result.battle = JsonToCardData(json["battle"].get<picojson::object>());
	}
	if (json["oldBattle"].is<picojson::object>()) {
		result.oldBattle = JsonToCardData(json["oldBattle"].get<picojson::object>());
	}
	if (json["id"].is<std::string>()) {
		result.id = json["id"].get<std::string>();
	}
	if (json["win"].is<double>()) {
		result.win = static_cast<int>(json["win"].get<double>());
	}

	return result;
}

picojson::object ConvertJson::RoomDataToJson(RoomData roomData)
{
	picojson::object result;
	result.insert(std::make_pair("player1Data", PlayerDataToJson(roomData.player1)));
	result.insert(std::make_pair("player2Data", PlayerDataToJson(roomData.player2)));
	std::string setState{ "waitAnalyze" };
	if (roomData.state == RoomState::waitAnalyze) {
		setState = "waitAnalyze";
	}
	result.insert(std::make_pair("state", picojson::value(setState)));

	return result;
}

RoomData ConvertJson::JsonToRoomData(picojson::object json)
{
	RoomData result;
	if (json["player1Data"].is<picojson::object>()) {
		result.player1 = JsonToPlayerData(json["player1Data"].get<picojson::object>());
	}
	if (json["player2Data"].is<picojson::object>()) {
		result.player2 = JsonToPlayerData(json["player2Data"].get<picojson::object>());
	}
	if (json["state"].is<picojson::object>()) {
		std::string state = json["state"].get<std::string>();
		if (state == "waitPlay") {
			result.state = RoomState::WaitPlay;
		}
		else if (state == "waitAnalyze") {
			result.state = RoomState::waitAnalyze;
		}
	}

	if (json["messageLog"].is<picojson::array>()) {
		picojson::array messageLog = json["messageLog"].get<picojson::array>();
		result.messageLog.clear();
		for (int i = 0; i < messageLog.size(); ++i) {
			if (messageLog[i].is<std::string>()) {
				auto wideMessage = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(messageLog[i].get<std::string>());
				auto shiftJisMessage = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wideMessage);
				result.messageLog.push_back(shiftJisMessage);
			}
		}
	}

	return result;
}

std::string ConvertJson::Escape0x5C(std::string text)
{
	for (int i = 0; i < text.size(); ++i) {
		unsigned char chara = text.at(i);
		if (chara == 0x5c) {
			text.insert(i, "\\");
			++i;
		}
	}
	return text;
}
