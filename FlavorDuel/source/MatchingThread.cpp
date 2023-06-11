#include "MatchingThread.h"
#include <windows.h>
#include <process.h>

using namespace Flavor;
namespace {
	constexpr auto endpoint = "matching";
}

MatchingThread::MatchingThread(std::string id, std::string type, std::vector<CardData> deck)
	:_id{ id }, _success{ false }, _type{ type }, _myDeckData{ deck }
{
}

MatchingThread::MatchingThread(std::string id, std::string type)
	:_id{ id }, _success{ false }, _type{ type }
{
	std::vector<CardData> nullData;
	_myDeckData = nullData;
}

bool MatchingThread::ThreadProc()
{
	Curl* curl = new Curl();
	picojson::object jsonObject;
	jsonObject.insert(std::make_pair("type", picojson::value(_type)));
	jsonObject.insert(std::make_pair("id", picojson::value(_id)));
	jsonObject.insert(std::make_pair("deck", ConvertJson::DeckDataToJson(_myDeckData)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	std::string error{""};
	std::string body{""};
	curl->Post(matchingURL, jsonString, error, body);
	if (error != "") {
		return false;
	}

	std::string recieveString = body;
	picojson::value responseValue;
	picojson::parse(responseValue, recieveString);
	picojson::object response = responseValue.get<picojson::object>();
	if (response["message"].is<std::string>()) {
		_message = response["message"].get<std::string>();
	}
	if (response["room"].is<picojson::object>()) {
		_roomData = ConvertJson::JsonToRoomData(response["room"].get<picojson::object>());
	}
	_success = true;
	return true;
}