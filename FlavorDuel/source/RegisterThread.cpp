#include "RegisterThread.h"
#include "CardObject.h"
#include "Curl.h"
#include <windows.h>
#include <process.h>
#include <picojson.h>
#include <algorithm>
using namespace Flavor;
namespace {
	constexpr auto RegisterURL = "http://localhost:9000/register";
}


Flavor::RegisterThread::RegisterThread(std::string id, std::string password)
	:_id{ id }, _password{ password }, _success{ false }
{
}

bool Flavor::RegisterThread::ThreadProc()
{
	Curl* curl = new Curl();
	picojson::object jsonObject;
	jsonObject.insert(std::make_pair("id", picojson::value(_id)));
	jsonObject.insert(std::make_pair("password", picojson::value(_password)));
	picojson::value value(jsonObject);
	std::string jsonString = value.serialize();

	std::string error{""};
	std::string body{""};
	curl->Post(RegisterURL, jsonString, error, body);
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