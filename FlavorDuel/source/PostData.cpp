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
	if (response["reason"].is<std::string>()) {
		_card->SetTips(response["reason"].get<std::string>());
	}
	return true;
}

LoginThread::LoginThread(std::string id, std::string password)
	:_id{ id }, _password{ password }, _success{ false }
{
}

bool LoginThread::ThreadProc()
{
	Curl* curl = new Curl();
	picojson::object jsonObject;
	jsonObject.insert(std::make_pair("id", picojson::value(_id)));
	jsonObject.insert(std::make_pair("password", picojson::value(_password)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	std::string error{""};
	std::string body{""};
	curl->Post(LoginURL, jsonString, error, body);
	if (error != "") {
		return false;
	}

	std::string recieveString = body;
	picojson::value responseValue;
	picojson::parse(responseValue, recieveString);
	picojson::object response = responseValue.get<picojson::object>();
	if (response["id"].is<std::string>()) {
		_data.id = response["id"].get<std::string>();
	}
	if (response["password"].is<std::string>()) {
		_data.password = response["password"].get<std::string>();
	}
	if (response["level"].is<double>()) {
		_data.level = (static_cast<int>(response["level"].get<double>()));
	}
	if (response["money"].is<double>()) {
		_data.money = (static_cast<int>(response["money"].get<double>()));
	}
	if (response["rank_rate"].is<double>()) {
		_data.rank = (static_cast<int>(response["rank_rate"].get<double>()));
	}
	_success = true;
	return true;
}
