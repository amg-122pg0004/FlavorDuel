#include "ModeInGame.h"
#include "CardFactory.h"
#include "BattleField.h"
#include "Hand.h"
#include "SequenceMessages.h"
#include "InGameThread.h"
#include "InGameUI.h"
#include "RoomState.h"
#include "ModeResult.h"
using namespace Flavor;

namespace {
	constexpr VECTOR MyHandPosition = { 600.0f,650.0f };
	constexpr VECTOR OpponentHandPosition = { 640.0f,50.0f };
	constexpr float PostInterval = 1.0f;
	constexpr auto BackgroundImagePath = "res/background2.png";
}

ModeInGame::ModeInGame(RoomData data, int myPlayerNumber)
	:_room{ data }
	, _myPlayerNumber{ myPlayerNumber }
	, _checkServerTimer{ 0.0f }
	, _playCard{ nullptr }
	, _cardFactory{ nullptr }
	, _judgeConfirm{ false }
{
	_backgroundImage = AppFrame::ImageServer::LoadGraph(BackgroundImagePath);
}

bool ModeInGame::Initialize() {
	AppFrame::ModeBase::Initialize();
	_cardFactory.reset(new CardFactory());
	_ingameThread.reset(new InGameThread(InGameThread::Type::CheckRoom));
	_ingameThread->ThreadStart();

	auto battlefield = std::make_unique<BattleField>(*this);
	_battleField = battlefield.get();
	this->GetObjectServer()->Add(std::move(battlefield));

	auto myHand = std::make_unique<Hand>(*this);
	_hand = myHand.get();
	myHand->SetPosition(MyHandPosition);
	this->GetObjectServer()->Add(std::move(myHand));

	auto winNumUI = std::make_unique<InGameUI>(*this);
	this->GetUICanvasServer()->Add(std::move(winNumUI));

	return false;
}

bool ModeInGame::Terminate() {
	return false;
}

bool ModeInGame::Update(InputManager& input) {
	if (_endMatch) {
		return false;
	}

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
		_checkServerTimer += this->GetStepTime() * 0.001f;
		if (_checkServerTimer > PostInterval) {
			_checkServerTimer = 0.0f;
			InGameThread::Type threadType{InGameThread::Type::CheckRoom};
			if (_playCard) {
				threadType = InGameThread::Type::PlayCard;
				_battleField->SetComfirm(false);
			}
			else if (_judgeConfirm) {
				threadType = InGameThread::Type::ConfirmJudge;
				_judgeConfirm = false;
			}
			_ingameThread.reset(new InGameThread(threadType));
			if (_playCard) {
				_ingameThread->SetPlayCard(std::move(_playCard));
			}
			_ingameThread->ThreadStart();
		}
	}
	return false;
}

bool ModeInGame::Render() {
	DrawGraph(0, 0, _backgroundImage, false);
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

void ModeInGame::Notify(InGameSequence message)
{
	for (auto&& observer : this->GetObserverList()) {
		observer->ReceiveNotify(this->GetSequence());
	}
}

void ModeInGame::SetRoomData(RoomData room)
{

	auto preRoom = _room;
	_room = room;

	if (_room.state == RoomState::FinishGame) {
		bool result{ GetPlayerData().win >= 3 };
		EndMatch(result);
	}

	auto playerData = GetPlayerData();
	_hand->SetCards(playerData.hand);
	_battleField->SetMyArea(playerData.battle);
	_battleField->SetOpponentArea(GetOpponentData().battle);

}

void ModeInGame::SetPlayCard(std::unique_ptr<CardData> data)
{
	_battleField->SetMyArea(*data);
	_playCard = std::move(data);
}

void Flavor::ModeInGame::SetJudgeConfirm()
{
	_judgeConfirm = true;
}

void Flavor::ModeInGame::EndMatch(bool win)
{
	_endMatch = true;
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeResult>(*this, win));
}

PlayerData ModeInGame::GetPlayerData()
{
	if (_myPlayerNumber == 1) {
		return 	_room.player1;
	}
	return 	_room.player2;
}

PlayerData ModeInGame::GetOpponentData()
{
	if (_myPlayerNumber == 1) {
		return 	_room.player2;
	}
	return 	_room.player1;
}

void ModeInGame::SetPlayerData(PlayerData data)
{
	if (_myPlayerNumber == 1) {
		_room.player1 = data;
	}
	else {
		_room.player2 = data;
	}
}
