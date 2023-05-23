/*****************************************************************//**
 * \file   PostData.h
 * \brief  httpでデータをPOSTする別スレッド処理クラス
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
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

	class RegisterThread : public ThreadBase {
	public:
		RegisterThread(std::string id, std::string password);
		bool ThreadProc()override;
		UserData GetUserData() { return _data; }
		bool GetSuccess() { return _success; }
	private:
		std::string _id;
		std::string _password;
		bool _success;
		UserData _data;
	};

	class MatchingThread : public ThreadBase {
	public:
		MatchingThread(std::string id);
		bool ThreadProc()override;
		bool GetSuccess() { return _success; }
		std::string GetMessage() { return _message; }
	private:
		std::string _id;
		bool _success;
		std::string _message;
	};
}


