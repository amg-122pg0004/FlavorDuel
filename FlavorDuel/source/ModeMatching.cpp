#include "ModeMatching.h"
#include "MatchingThread.h"
#include "ModeHome.h"
#include "ModeInGame.h"
#include "MatchingUI.h"
using namespace Flavor;
namespace {
	constexpr float RePostTimer = 1.0f;
}

ModeMatching::ModeMatching(MatchType type, std::vector<CardData> deckdata, ModeHome& mode)
	:_state{ MatchState::Finding }, _timer{ 0.0f }, _myDeckData{ deckdata }, _modeHome{ mode }
{
	auto app = AppFrame::ApplicationBase::GetInstance();
	_matchingThread.reset(new MatchingThread(app->GetAppData()->GetData<UserData>().id, "StartMatching", _myDeckData));
	_matchingThread->ThreadStart();
}

bool ModeMatching::Initialize()
{
	ModeBase::Initialize();
	auto matchingUI = std::make_unique<MatchingUI>(*this);
	this->GetUICanvasServer()->Add(std::move(matchingUI));
	return false;
}

bool ModeMatching::Terminate()
{
	ModeBase::Terminate();
	return false;
}

bool ModeMatching::Update(InputManager& input)
{
	AppFrame::ModeServer::GetInstance()->PauseProcessUnderLayer();
	ModeBase::Update(input);

	if (!_matchingThread) {
		_timer += this->GetStepTime() * 0.001f;
		if (_timer >= RePostTimer) {
			_timer = 0.0f;
			auto app = AppFrame::ApplicationBase::GetInstance();
			_matchingThread.reset(new MatchingThread(app->GetAppData()->GetData<UserData>().id, "CheckMatching"));
			_matchingThread->ThreadStart();
		}
	}

	if (!_matchingThread) {
		return false;
	}

	if (!_matchingThread->IsThreadExec()) {
		if (_state == MatchState::Cancel) {
			AppFrame::ModeServer::GetInstance()->Del(this);
			return false;
		}
		_message = _matchingThread->GetReceiveMessage();
		if (_message == "FindingNow") {

		}
		else if (_message == "MatchingSuccess") {
			_state = MatchState::Complete;
			auto room = _matchingThread->GetRoomData();
			auto app = AppFrame::ApplicationBase::GetInstance();
			std::string id = app->GetAppData()->GetData<UserData>().id;
			int myPlayerNumber{ 1 };
			if (room.player2.id == id) {
				myPlayerNumber = 2;
			}
			ChangeModeInGame(room, myPlayerNumber);
		}
		else if (_message == "StopMatching") {

		}
		_matchingThread.release();
	}




	return false;
}

bool ModeMatching::Render()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	auto app = AppFrame::ApplicationBase::GetInstance();
	DrawBox(0,0, app->DispSizeW(),app->DispSizeH(),AppFrame::Color::Black,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	ModeBase::Render();
	return false;
}

bool ModeMatching::Debug()
{
	ModeBase::Debug();
	return false;
}

void Flavor::ModeMatching::ChangeModeInGame(RoomData room, int myPlayerNumber)
{
	AppFrame::ModeServer::GetInstance()->Add(std::make_unique<ModeInGame>(room, myPlayerNumber));
	AppFrame::ModeServer::GetInstance()->Del(this);
	AppFrame::ModeServer::GetInstance()->Del(&_modeHome);
}

void Flavor::ModeMatching::StopMatching()
{
	auto app = AppFrame::ApplicationBase::GetInstance();
	_matchingThread.reset(new MatchingThread(app->GetAppData()->GetData<UserData>().id, "StopMatching"));
	_matchingThread->ThreadStart();
	_state = MatchState::Cancel;
}
