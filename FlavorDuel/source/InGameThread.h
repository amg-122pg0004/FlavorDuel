/*****************************************************************//**
 * \file   MatchingThread.h
 * \brief  �}�b�`���OPOST�p�@�ʃX���b�h�����N���X
 *
 * \author �y�������Y
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
		InGameThread();
		bool ThreadProc()override;
		bool GetSuccess() { return _success; }
		RoomData GetReceiveRoomData() { return _receiveData; }
		void SetPlayCard(std::unique_ptr<CardData> data) { _playCard = std::move(data); }
	private:
		bool _success;
		RoomData _receiveData;
		std::unique_ptr<CardData> _playCard;
	};
}