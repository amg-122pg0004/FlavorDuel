/*****************************************************************//**
 * \file   LoginThread.h
 * \brief  ログイン用　別スレッド処理クラス
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "Curl.h"
#include "ThreadBase.h"
#include "CardDataStruct.h"
#include "UserDataStruct.h"

namespace Flavor {
	class CardObject;

	class LoginThread : public ThreadBase {
	public:
		LoginThread(std::string id, std::string password);
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