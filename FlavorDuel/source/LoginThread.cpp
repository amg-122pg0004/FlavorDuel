#include "LoginThread.h"
#include <windows.h>
#include <process.h>
#include <picojson.h>
#include <algorithm>
#include "ConvertJson.h"
using namespace Flavor;
namespace {
	constexpr auto LoginURL = "http://localhost:9000/login";
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
	if (response["deck"].is<std::string>()) {
		picojson::value deckValue;
		picojson::parse(deckValue, response["deck"].get<std::string>());
		picojson::array deck = deckValue.get<picojson::array>();
		_data.deck = ConvertJson::JsonToDeckData(deck);;
	}
	_success = true;
	return true;
}