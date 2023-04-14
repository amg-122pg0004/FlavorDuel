#include "PostData.h"
#include "CardObject.h"
#include <windows.h>
#include <process.h>
#include <picojson.h>
#include <algorithm>
using namespace Flavor;
namespace {
	constexpr auto TestURL = "http://localhost:9000";
}

bool PostData::PostCardData(CardObject* card)
{
	Curl* curl = new Curl();

	picojson::object jsonObject;
	auto nameUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(card->GetCardName());
	auto textUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(card->GetCardText());
	jsonObject.insert(std::make_pair("name", picojson::value(nameUTF8)));
	jsonObject.insert(std::make_pair("text", picojson::value(textUTF8)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	curl->post(TestURL, jsonString, [](std::string error, std::string body) {
		if (error != "") {
			std::cerr << "ERROR: " << error << std::endl;
		}
		else {
			std::cout << "POST Response body:" << std::endl;
			std::cout << body << std::endl;
		}
		});

	auto wide = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(curl->GetBody());
	auto shiftJisText = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wide);

	for (int i = 0; i < shiftJisText.size(); ++i) {
		unsigned char chara = shiftJisText.at(i);
		if (chara == 0x5c) {
			shiftJisText.insert(i, "\\");
			++i;
		}
	}

	picojson::value responseValue;
	picojson::parse(responseValue, shiftJisText);
	picojson::object response = responseValue.get<picojson::object>();
	if (response["attack"].is<double>()) {
		card->SetAttack(static_cast<int>(response["attack"].get<double>() * 100));
	}
	if (response["defense"].is<double>()) {
		card->SetDefense(static_cast<int>(response["defense"].get<double>() * 100));
	}
	if (response["reason"].is<std::string>()) {
		card->SetTips(response["reason"].get<std::string>());
	}
	return true;
}

Flavor::PostThread::PostThread(CardObject* card)
	:_card{card}
{
}

bool Flavor::PostThread::ThreadProc()
{
	Curl* curl = new Curl();

	picojson::object jsonObject;
	auto nameUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_card->GetCardName());
	auto textUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_card->GetCardText());
	jsonObject.insert(std::make_pair("name", picojson::value(nameUTF8)));
	jsonObject.insert(std::make_pair("text", picojson::value(textUTF8)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	curl->post(TestURL, jsonString, [](std::string error, std::string body) {
		if (error != "") {
			std::cerr << "ERROR: " << error << std::endl;
		}
		else {
			std::cout << "POST Response body:" << std::endl;
			std::cout << body << std::endl;
		}
		});

	auto wide = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(curl->GetBody());
	auto shiftJisText = AppFrame::CharacterCodeConvert::ConvertWideToShiftJIS(wide);

	for (int i = 0; i < shiftJisText.size(); ++i) {
		unsigned char chara = shiftJisText.at(i);
		if (chara == 0x5c) {
			shiftJisText.insert(i, "\\");
			++i;
		}
	}

	picojson::value responseValue;
	picojson::parse(responseValue, shiftJisText);
	picojson::object response = responseValue.get<picojson::object>();
	if (response["attack"].is<double>()) {
		_card->SetAttack(static_cast<int>(response["attack"].get<double>() * 100));
	}
	if (response["defense"].is<double>()) {
		_card->SetDefense(static_cast<int>(response["defense"].get<double>() * 100));
	}
	if (response["reason"].is<std::string>()) {
		_card->SetTips(response["reason"].get<std::string>());
	}
	return true;
}
