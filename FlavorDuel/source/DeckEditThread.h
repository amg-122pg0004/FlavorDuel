#pragma once
#include "appframe.h"
#include "Curl.h"
#include <picojson.h>
#include "ThreadBase.h"
#include "CardDataStruct.h"
#include "UserDataStruct.h"
#include "ConvertJson.h"

namespace Flavor {
	class CardObject;
	class DeckEditThread : public ThreadBase {
	public:
		DeckEditThread(std::string id,std::vector<CardData> deck);
		bool ThreadProc()override;
		bool GetSuccess() { return _success; }
		std::string GetReceiveMessage() { return _message; }
		UserData GetUserData() { return _userData; }
	private:
		std::string _id;
		bool _success;
		std::string _message;
		std::vector<CardData> _editDeckData;
		UserData _userData;
	};
}
