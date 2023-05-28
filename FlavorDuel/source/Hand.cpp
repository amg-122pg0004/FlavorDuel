#include "Hand.h"
#include "CardObject.h"
#include "CardFactory.h"
#include "ModeInGame.h"
using namespace Flavor;

namespace {
	constexpr int StartHandNumber = 5;
	constexpr float CardsInterval = 180.0f;
	constexpr float cardScale = 0.5f;
}
Hand::Hand(ModeInGame& modeInGame) : _modeInGame{ modeInGame }, _playCard{ false }
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
	CardObject* selectCard{ nullptr };
	for (auto&& card : _cards) {
		card->Update(input);
		if (card->GetSelected()) {
			_playCard = true;
			selectCard = card.get();
		}
	}
	if (selectCard) {
		auto playerData = _modeInGame.GetPlayerData();
		playerData.battle.cg = selectCard->GetImage();
		playerData.battle.name = selectCard->GetCardName();
		playerData.battle.flavorText = selectCard->GetCardText();
		for (auto itr = _cards.begin(); itr != _cards.end(); ++itr) {
			if ((*itr).get() == selectCard) {
				_cards.erase(itr);
				break;
			}
		}
		_modeInGame.SetPlayerData(playerData);
	}
}

void Hand::Render() {
	int handNumber = static_cast<int>(_cards.size());
	float halfHandNumber = static_cast<float>(handNumber) / 2.0f;
	for (int i = 0; i < handNumber; ++i) {
		VECTOR adjustPosition = VAdd(this->GetPosition(), { CardsInterval * (static_cast<float>(i) - halfHandNumber) });
		_cards.at(i)->SetPosition(adjustPosition);
		_cards.at(i)->SetSelected(false);
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
void Hand::SetCards(std::vector<CardData> data)
{
	_cards.clear();
	for (auto&& card : data) {
		_cards.emplace_back(CardFactory::CreateCard(card));
	}
}
