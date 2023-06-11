#include "DeckEditThread.h"
#include <windows.h>
#include <process.h>

using namespace Flavor;
namespace {
	constexpr auto endpoint = "edit";
}

DeckEditThread::DeckEditThread(std::string id, std::vector<CardData> deck)
	:_id{ id }
	, _editDeckData{ deck }
{

}

bool DeckEditThread::ThreadProc()
{
	Curl* curl = new Curl();
	picojson::object jsonObject;
	jsonObject.insert(std::make_pair("id", picojson::value(_id)));
	jsonObject.insert(std::make_pair("deck", ConvertJson::DeckDataToJson(_editDeckData)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	std::string error{""};
	std::string body{""};
	std::string url{URL::Server};
	url += endpoint;
	curl->Post(url, jsonString, error, body);
	if (error != "") {
		return false;
	}

	std::string recieveString = body;
	picojson::value responseValue;
	picojson::parse(responseValue, recieveString);
	picojson::object response = responseValue.get<picojson::object>();
	if (response["id"].is<std::string>()) {
		_userData.id = response["id"].get<std::string>();
	}
	if (response["password"].is<std::string>()) {
		_userData.password = response["password"].get<std::string>();
	}
	if (response["level"].is<double>()) {
		_userData.level = (static_cast<int>(response["level"].get<double>()));
	}
	if (response["money"].is<double>()) {
		_userData.money = (static_cast<int>(response["money"].get<double>()));
	}
	if (response["rank_rate"].is<double>()) {
		_userData.rank = (static_cast<int>(response["rank_rate"].get<double>()));
	}
	if (response["deck"].is<std::string>()) {
		picojson::value deckValue;
		picojson::parse(deckValue, response["deck"].get<std::string>());
		picojson::array deck = deckValue.get<picojson::array>();
		_userData.deck = ConvertJson::JsonToDeckData(deck);;
	}
	_success = true;
	return true;
}


