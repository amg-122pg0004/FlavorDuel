#include "ModeInGame.h"
#include "CardFactory.h"
#include "BattleField.h"
#include "Deck.h"
#include "Hand.h"
#include "SequenceMessages.h"
#include "MessageLog.h"
using namespace Flavor;

namespace {
	constexpr VECTOR MyHandPosition = { 640.0f,650.0f };
	constexpr VECTOR OpponentHandPosition = { 640.0f,50.0f };;
}

ModeInGame::ModeInGame(DeckData myData, DeckData opponentData)
	:_myData{ myData }
	, _opponentData{ opponentData }
	, _cardFactory{ nullptr }
{
}

bool ModeInGame::Initialize() {
	AppFrame::ModeBase::Initialize();

	_cardFactory.reset(new CardFactory);

	auto battlefirld = std::make_unique<BattleField>(*this);

	auto myDeck = std::make_unique<Deck>(*this);
	myDeck->SetDeckData(_myData);
	myDeck->Shuffle();
	auto opponentDeck = std::make_unique<Deck>(*this);
	opponentDeck->SetDeckData(_opponentData);
	opponentDeck->Shuffle();

	auto myHand = std::make_unique<Hand>(battlefirld.get(),Hand::Owner::Self);
	myHand->SetDeck(myDeck.get());
	myHand->SetPosition(MyHandPosition);
	auto opponentHand = std::make_unique<Hand>(battlefirld.get(), Hand::Owner::Opponent);
	opponentHand->SetDeck(opponentDeck.get());
	opponentHand->SetPosition(OpponentHandPosition);

	this->Subscribe(myDeck.get());
	this->Subscribe(opponentDeck.get());
	this->Subscribe(myHand.get());
	this->Subscribe(opponentHand.get());


	this->GetObjectServer()->Add(std::move(myHand));
	this->GetObjectServer()->Add(std::move(opponentHand));
	this->GetObjectServer()->Add(std::move(myDeck));
	this->GetObjectServer()->Add(std::move(opponentDeck));

	this->GetObjectServer()->Add(std::move(battlefirld));

	auto messageLog = std::make_unique<MessageLog>();
	_messageLog = messageLog.get();
	this->GetUICanvasServer()->Add(std::move(messageLog));
	this->Notify(SequenceMessages::GameStart);

	return false;
}

bool ModeInGame::Terminate() {
	return false;
}

bool ModeInGame::Update(InputManager& input) {
	ModeBase::Update(input);
	return false;
}

bool ModeInGame::Render() {
	ModeBase::Render();
	return false;
}

bool ModeInGame::Debug() {
	ModeBase::Debug();
	return false;
}

void ModeInGame::Subscribe(IObserverSequence* observer)
{
	this->GetObserverList().emplace_back(observer);
}

void ModeInGame::Notify(SequenceMessages message)
{
	for (auto&& observer : this->GetObserverList()) {
		observer->ReceiveNotify(this->GetSequence());
	}
}
