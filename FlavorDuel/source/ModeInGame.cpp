#include "ModeInGame.h"
#include "CardFactory.h"
#include "BattleField.h"
#include "Hand.h"
#include "SequenceMessages.h"
#include "MessageLog.h"
#include "InGameThread.h"
using namespace Flavor;

namespace {
	constexpr VECTOR MyHandPosition = { 640.0f,650.0f };
	constexpr VECTOR OpponentHandPosition = { 640.0f,50.0f };
	constexpr float PostInterval = 2.0f;
}
ModeInGame::ModeInGame(RoomData data, int myPlayerNumber)
	:_room{ data }, _messageLog{ nullptr }, _myPlayerNumber{ myPlayerNumber }, _timer{ 0.0f }
{
}

bool ModeInGame::Initialize() {
	AppFrame::ModeBase::Initialize();
	_ingameThread.reset(new InGameThread(_room));
	_ingameThread->ThreadStart();

	auto battlefield = std::make_unique<BattleField>(*this);
	_battleField = battlefield.get();
	this->GetObjectServer()->Add(std::move(battlefield));

	auto myHand = std::make_unique<Hand>(*this);
	_hand = myHand.get();
	myHand->SetPosition(MyHandPosition);
	this->GetObjectServer()->Add(std::move(myHand));

	auto messageLog = std::make_unique<MessageLog>();
	_messageLog = messageLog.get();
	this->GetUICanvasServer()->Add(std::move(messageLog));

	return false;
}

bool ModeInGame::Terminate() {
	return false;
}

bool ModeInGame::Update(InputManager& input) {
	ModeBase::Update(input);

	if (_ingameThread) {
		if (!_ingameThread->IsThreadExec()) {
			if (_ingameThread->GetSuccess()) {
				this->SetRoomData(_ingameThread->GetReceiveRoomData());
			}
			_ingameThread.release();
		}
	}
	else {
		_timer += this->GetStepTime() * 0.001f;
		if (_timer > PostInterval) {
			_timer = 0.0f;
			_ingameThread.reset(new InGameThread(_room));
			_ingameThread->ThreadStart();
		}
	}

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

void Flavor::ModeInGame::SetRoomData(RoomData room)
{
	_room = room;
	auto playerData = GetPlayerData();
	_hand->SetCards(playerData.hand);
	_battleField->SetMyArea(playerData.battle);
	_battleField->SetOpponentArea(GetOpponentData().battle);
}

PlayerData Flavor::ModeInGame::GetPlayerData()
{
	if (_myPlayerNumber == 1) {
		return 	_room.player1;
	}
	return 	_room.player2;
}

PlayerData Flavor::ModeInGame::GetOpponentData()
{
	if (_myPlayerNumber == 1) {
		return 	_room.player2;
	}
	return 	_room.player1;
}

void Flavor::ModeInGame::SetPlayerData(PlayerData data)
{
	if (_myPlayerNumber == 1) {
		_room.player1 = data;
	}
	else {
		_room.player2 = data;
	}
}
