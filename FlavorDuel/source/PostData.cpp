#include "PostData.h"
#include "CardObject.h"
#include <windows.h>
#include <process.h>
#include <picojson.h>
#include <algorithm>
using namespace Flavor;
namespace {
	constexpr auto TestURL = "http://localhost:9000";
	constexpr auto LoginURL = "http://localhost:9000/login";
	constexpr auto RegisterURL = "http://localhost:9000/register";
	constexpr auto matchingURL = "http://localhost:9000/matching";
}

PostThread::PostThread(CardObject* card)
	:_card{ card }
{
}

bool PostThread::ThreadProc()
{
	Curl* curl = new Curl();

	picojson::object jsonObject;
	auto nameUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_card->GetCardName());
	auto textUTF8 = AppFrame::CharacterCodeConvert::ConvertShiftJISToUTF8(_card->GetCardText());
	jsonObject.insert(std::make_pair("name", picojson::value(nameUTF8)));
	jsonObject.insert(std::make_pair("text", picojson::value(textUTF8)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	std::string error;
	std::string body;
	curl->Post(TestURL, jsonString, error, body);

	auto wide = AppFrame::CharacterCodeConvert::ConvertUTF8ToWide(body);
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
	return true;
}