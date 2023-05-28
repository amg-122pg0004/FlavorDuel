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
#include "ThreadBase.h"
#include "CardDataStruct.h"
namespace Flavor {
	class CardObject;
	class InGameThread : public ThreadBase {
	public:
		InGameThread(RoomData postData);
		bool ThreadProc()override;
		bool GetSuccess() { return _success; }
		RoomData GetReceiveRoomData() { return _receiveData; }
	private:
		bool _success;
		RoomData _postData;
		RoomData _receiveData;
	};
}