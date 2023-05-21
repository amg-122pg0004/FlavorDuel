#pragma once
#include "appframe.h"
#include "Curl.h"
#include "ThreadBase.h"
#include "UserDataStruct.h"

namespace Flavor {
	class CardObject;

	class PostThread : public ThreadBase {
	public:
		PostThread(CardObject* card);
		bool ThreadProc()override;
		CardObject* GetCard() { return _card; }
	private:
		CardObject* _card;
	};

	class LoginThread : public ThreadBase {
	public:
		LoginThread(std::string id,std::string password);
		bool ThreadProc()override;
		UserData GetUserData() { return _data; }
		bool GetSuccess() { return _success; }
	private:
		std::string _id;
		std::string _password;
		bool _success;
		UserData _data;
	};
}


