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

		MessageLog* GetMessageLog() { return _messageLog; }
		RoomData GetRoomData() { return _room; }
		PlayerData GetPlayerData();
		PlayerData GetOpponentData();
		void SetPlayerData(PlayerData data);
		void SetRoomData(RoomData room);
		void SetPlayCard(std::unique_ptr<CardData> data);

		std::unique_ptr<CardFactory>& GetCardFactory() { return _cardFactory; }
	private:
		InGameSequence _sequence;
		std::unique_ptr<CardFactory> _cardFactory;
		std::unique_ptr<InGameThread> _ingameThread;
		BattleField* _battleField;
		Hand* _hand;
		MessageLog* _messageLog;
		RoomData _room;
		int _myPlayerNumber;
		int _backgroundImage;
		float _timer;
		std::unique_ptr<CardData> _playCard;
	};
}