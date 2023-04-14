#include "Hand.h"
#include "Deck.h"
#include "CardObject.h"
#include "BattleField.h"

namespace {
	constexpr int StartHandNumber = 5;
	constexpr float CardsInterval = 180.0f;
	constexpr float cardScale = 0.5f;
}
namespace Flavor {
	Hand::Hand(BattleField* battleField, Owner owner)
		:_deck{ nullptr }
		, _adjustHands{ false }
		, _battleField{ battleField }
		, _owner{ owner }
		, _playCard{false}
	{

	}

	Hand::~Hand() {

	}

	void Hand::Init() {

	}

	void Hand::Terminate() {

	}

	void Hand::Update(InputManager& input) {
		if (_playCard) {
			return;
		}
		CardObject* selectedCard{ nullptr };
		for (auto&& card : _cards) {
			card->Update(input);
			if (card->GetSelected()) {
				selectedCard = card.get();
				_playCard = true;
			}
		}
		if (_owner == Owner::Self) {
			_battleField->SetMyArea(selectedCard);
		}
		else {
			_battleField->SetEnemyArea(selectedCard);
		}
	}

	void Hand::Render() {
		if (_adjustHands) {
			int handNumber = static_cast<int>(_cards.size());
			float halfHandNumber = static_cast<float>(handNumber) / 2.0f;
			for (int i = 0; i < handNumber; ++i) {
				VECTOR adjustPosition = VAdd(this->GetPosition(), { CardsInterval * (static_cast<float>(i) - halfHandNumber) });
				_cards.at(i)->SetPosition(adjustPosition);
				_cards.at(i)->SetSelected(false);
			}
			_adjustHands = false;
		}

		for (auto&& card : _cards) {
			card->Render();
		}
	}

	void Hand::Debug() {

	}
	void Hand::ReceiveNotify(SequenceMessages sequence)
	{
		switch (sequence)
		{
		case GameStart:
			for (int i = 0; i < StartHandNumber; ++i) {
				_cards.emplace_back(_deck->DrawCard());
			}
			_adjustHands = true;
			break;
		case TurnStart:
			_playCard = false;
			break;
		case CardSelect:
			break;
		case Battle:
			break;
		case TurnEnd:
			break;
		default:
			break;
		}
	}
}
