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
Hand::Hand(ModeInGame& modeInGame) : _modeInGame{ modeInGame }
{

}

Hand::~Hand() {

}

void Hand::Init() {

}

void Hand::Terminate() {

}

void Hand::Update(InputManager& input) {
	if (_modeInGame.GetPlayerData().battle.name != "") {
		return;
	}

	CardObject* selectCard{ nullptr };
	for (auto&& card : _cards) {
		card->Update(input);
		if (card->GetSelected()) {
			selectCard = card.get();
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
void Hand::ReceiveNotify(InGameSequence sequence)
{
}
void Hand::SetCards(std::vector<CardData> data)
{
	//現在の手札とセットしようとしている手札が同じなら処理を行わない
	bool refreshFlag{ false };
	if (_cards.size() == data.size()) {
		for (int i = 0; i < _cards.size(); ++i) {
			if (_cards.at(i)->GetName() != data.at(i).name) {
				refreshFlag = true;
			}
		}
	}
	else {
		refreshFlag = true;
	}

	if (!refreshFlag) {
		return;
	}

	_cards.clear();
	for (auto&& card : data) {
		_cards.emplace_back(_modeInGame.GetCardFactory()->CreateCard(card));
	}
}
