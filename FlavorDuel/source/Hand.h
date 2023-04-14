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
namespace Flavor {
	using AppFrame::InputManager;
	class CardObject;
	class Deck;
	class BattleField;

	class Hand : public AppFrame::ObjectBase, public IObserverSequence {
	public:
		enum class  Owner { Self, Opponent };
		Hand(BattleField* battleField, Owner owner);
		~Hand();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;

		void ReceiveNotify(SequenceMessages sequence)override;

		void SetDeck(Deck* deckPointer) { _deck = deckPointer; }
	private:
		bool _playCard;
		Owner _owner;
		Deck* _deck;
		std::vector<std::unique_ptr<CardObject>> _cards;
		bool _adjustHands;
		BattleField* _battleField;
	};
}