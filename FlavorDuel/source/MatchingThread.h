/*****************************************************************//**
 * \file   MatchingThread.h
 * \brief  マッチングPOST用　別スレッド処理クラス
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
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
	class MatchingThread : public ThreadBase {
	public:
		MatchingThread(std::string id, std::string type, std::vector<CardData> deck);
		MatchingThread(std::string id, std::string type);
		bool ThreadProc()override;
		bool GetSuccess() { return _success; }
		std::string GetReceiveMessage() { return _message; }
		RoomData GetRoomData() { return _roomData; }
	private:
		std::string _id;
		std::string _type;
		bool _success;
		std::string _message;
		std::vector<CardData> _myDeckData;
		RoomData _roomData;
	};
}