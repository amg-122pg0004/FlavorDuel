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
Hand::Hand(ModeInGame& modeInGame) : _modeInGame{ modeInGame }, _canPlay{ true }
{

}

Hand::~Hand() {

}

void Hand::Init() {

}

void Hand::Terminate() {

}

void Hand::Update(InputManager& input) {
	if (!_canPlay) {
		return;
	}

	CardObject* selectCard{ nullptr };
	for (auto&& card : _cards) {
		card->Update(input);
		if (card->GetSelected()) {
			selectCard = card.get();
			_canPlay = false;
		}
	}
	if (selectCard) {
		_modeInGame.SetPlayCard(std::make_unique<CardData>(selectCard->GetCardData()));
		for (int i = 0; i < _cards.size(); ++i) {
			if (_cards.at(i).get() == selectCard) {
				_cards.erase(_cards.begin() + i);
				break;
			}
		}
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
}
void Hand::SetCards(std::vector<CardData> data)
{
	_cards.clear();
	for (auto&& card : data) {
		_cards.emplace_back(CardFactory::CreateCard(card));
	}
}
