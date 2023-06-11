#include "InGameThread.h"
#include <windows.h>
#include <process.h>
#include "ConvertJson.h"
#include "UserDataStruct.h"

using namespace Flavor;
namespace {
	constexpr auto endpoint = "ingame";
}

InGameThread::InGameThread(Type postType)
	:_success{ false }, _type{ postType }
{
}

bool InGameThread::ThreadProc()
{
	Curl* curl = new Curl();

	picojson::object postJson;

	std::string typeMessage{"CheckRoom"};
	if (_playCard) {
		typeMessage = "PlayCard";
		postJson.insert(std::make_pair("play", ConvertJson::CardDataToJson(*_playCard.get())));
	}
	else if (_type == Type::ConfirmJudge) {
		typeMessage = "ConfirmJudge";
	}
	postJson.insert(std::make_pair("type", typeMessage));

	std::string id = AppFrame::ApplicationBase::GetInstance()->GetAppData()->GetData<UserData>().id;
	postJson.insert(std::make_pair("id", picojson::value(id)));
	picojson::value value(postJson);
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
	if (response["room"].is<picojson::object>()) {
		_receiveData = ConvertJson::JsonToRoomData(response["room"].get<picojson::object>());
		_success = true;
	}

	return true;
}