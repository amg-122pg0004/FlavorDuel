/*****************************************************************//**
 * \file   ModeInGame.h
 * \brief  インゲーム　Sequenceの通知を行う
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
#include "ISubjectSequence.h"
#include "CardFactory.h"
#include "InGameThread.h"
namespace Flavor {
	using AppFrame::InputManager;
	class MessageLog;
	class Hand;
	class BattleField;

	class ModeInGame : public AppFrame::ModeBase, private ISubjectSequence {
	public:
		ModeInGame(RoomData data, int myPlayerNumber);
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();
		void Subscribe(IObserverSequence* observer)override;
		void Notify(InGameSequence message)override;

		RoomData GetRoomData() { return _room; }
		PlayerData GetPlayerData();
		PlayerData GetOpponentData();
		void SetPlayerData(PlayerData data);
		void SetRoomData(RoomData room);
		void SetPlayCard(std::unique_ptr<CardData> data);
		void SetJudgeConfirm();
		std::unique_ptr<CardFactory>& GetCardFactory() { return _cardFactory; }

		void EndMatch(bool win);
	private:
		InGameSequence _sequence;
		std::unique_ptr<CardFactory> _cardFactory;
		std::unique_ptr<InGameThread> _ingameThread;
		BattleField* _battleField;
		Hand* _hand;
		RoomData _room;
		int _myPlayerNumber;
		int _backgroundImage;
		float _checkServerTimer;
		std::unique_ptr<CardData> _playCard;
		bool _judgeConfirm;
		bool _endMatch;
	};
}