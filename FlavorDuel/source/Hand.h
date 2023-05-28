/*****************************************************************//**
 * \file   Hand.h
 * \brief  手札のカード
 *
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include "IObserverSequence.h"
#include "CardDataStruct.h"

namespace Flavor {
	using AppFrame::InputManager;
	class CardObject;
	class ModeInGame;

	class Hand : public AppFrame::ObjectBase, public IObserverSequence {
	public:
		Hand(ModeInGame& modeInGame);
		~Hand();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;

		void ReceiveNotify(SequenceMessages sequence)override;
		void SetCards(std::vector<CardData> data);
	private:
		ModeInGame& _modeInGame;
		bool _playCard;
		std::vector<std::unique_ptr<CardObject>> _cards;
	};
}