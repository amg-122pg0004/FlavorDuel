/*****************************************************************//**
 * \file   Deck.h
 * \brief  デッキのカード
 * 
 * \author 土居将太郎
 * \date   May 2023
 *********************************************************************/

#pragma once
#include "appframe.h"
#include "CardDataStruct.h"
#include "IObserverSequence.h"
namespace Flavor {
	using AppFrame::InputManager;
	class ModeInGame;
	class CardObject;

	using DeckCards = std::vector<std::unique_ptr<CardObject>>;

	class Deck : public AppFrame::ObjectBase, public IObserverSequence
	{
	public:
		Deck(ModeInGame& modeInGame);
		~Deck();
		void Init()override;
		void Terminate()override;
		void Update(InputManager& input)override;
		void Render()override;
		void Debug()override;

		void Shuffle();
		std::unique_ptr<CardObject> DrawCard();
		void SetDeckData(DeckData data);

		void ReceiveNotify(SequenceMessages sequence)override;
	private:
		ModeInGame& _modeInGame;
		std::string _name;
		DeckCards _cards;
	};
}