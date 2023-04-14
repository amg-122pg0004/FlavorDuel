#include "Deck.h"
#include "CardFactory.h"
#include "CardObject.h"
#include "ModeInGame.h"
#include <algorithm>
namespace Flavor {
	Deck::Deck(ModeInGame& modeInGame)
		:_modeInGame{ modeInGame }
	{

	}

	Deck::~Deck() {

	}

	void Deck::Init() {

	}

	void Deck::Terminate() {

	}

	void Deck::Update(InputManager& input) {

	}

	void Deck::Render() {

	}

	void Deck::Debug() {

	}

	void Deck::Shuffle() {
		std::shuffle(_cards.begin(), _cards.end(), AppFrame::Random::GetSeed());
	}

	std::unique_ptr<CardObject> Deck::DrawCard() {
		if (_cards.empty()) {
			return nullptr;
		}
		std::unique_ptr<CardObject> drawCard = std::move(*_cards.begin());
		_cards.erase(_cards.begin());
		return drawCard;
	}

	void Deck::SetDeckData(DeckData data)
	{
		for (auto&& cardData : data.cards) {
			auto card = _modeInGame.GetCardFactory()->CreateCard(cardData);
			_cards.emplace_back(std::move(card));
		}
	}
	void Deck::ReceiveNotify(SequenceMessages sequence)
	{
	}
}
