/*****************************************************************//**
 * \file   ModeMatching.h
 * \brief  マッチングモード
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
namespace Flavor {
	using AppFrame::InputManager;
	class CardFactory;
	class MessageLog;
	class MatchingThread;
	class ModeHome;

	enum class MatchType{ Casual,Rank };
	enum class MatchState { Finding, Complete,Cancel };

	class ModeMatching : public AppFrame::ModeBase {
	public:
		ModeMatching(MatchType type,std::vector<CardData> deckdata, ModeHome& mode);
		bool Initialize();
		bool Terminate();
		bool Update(InputManager& input);
		bool Render();
		bool Debug();

		void ChangeModeInGame(RoomData room,int myPlayerNumber);
		void StopMatching();
	private:
		ModeHome& _modeHome;

		std::unique_ptr<MatchingThread> _matchingThread;
		std::vector<CardData> _myDeckData;
		std::string _message;
		MatchState _state;
		float _timer;
	};
}