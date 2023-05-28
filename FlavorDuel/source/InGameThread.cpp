#include "InGameThread.h"
#include <windows.h>
#include <process.h>
#include "ConvertJson.h"
#include "UserDataStruct.h"

using namespace Flavor;
namespace {
	constexpr auto ingameURL = "http://localhost:9000/ingame";
}

InGameThread::InGameThread(RoomData postData) :_success{ false }, _postData{ postData }, _receiveData{ postData }
{
}

bool InGameThread::ThreadProc()
{
	Curl* curl = new Curl();

	picojson::object postJson;
	postJson.insert(std::make_pair("room", ConvertJson::RoomDataToJson(_postData)));
	std::string id = AppFrame::ApplicationBase::GetInstance()->GetAppData()->GetData<UserData>().id;
	postJson.insert(std::make_pair("id", picojson::value(id)));
	picojson::value value(postJson);
	std::string jsonString = value.serialize();

	std::string error{""};
	std::string body{""};
	curl->Post(ingameURL, jsonString, error, body);
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