#include "BattleField.h"
#include "CardObject.h"
#include "PostData.h"
#include "ModeInGame.h"
#include "MessageWindow.h"
#include "MessageLog.h"
#include "CardFactory.h"
using namespace Flavor;

namespace {
	AppFrame::VECTOR2<int> MyPosition = { 400,350 };
	AppFrame::VECTOR2<int> OpponentPosition = { 750,300 };
}

BattleField::BattleField(ModeInGame& mode)
	:_modeInGame{ mode }
	, _myCard{ nullptr }
	, _opponentCard{ nullptr }
	, _settMyCard{ false }
	, _setOpponentCard{ false }
	, _threadHolder{ nullptr }
{
	_font = CreateFontToHandle("result", 60, 8, DX_FONTTYPE_ANTIALIASING);
}

BattleField::~BattleField()
{
	DeleteFontToHandle(_font);
}

void BattleField::Init()
{

}

void BattleField::Terminate()
{
}

void BattleField::Update(InputManager& input)
{
	/*
	if (_threadHolder != nullptr) {
		if (!_threadHolder->IsThreadExec()) {
			auto messageLogPtr = _modeInGame.GetMessageLog();
			messageLogPtr->AddChildCanvas(std::make_unique<MessageWindow>(_threadHolder->GetCard()->GetTips()));
			_threadHolder.release();
		}
	}
	if (input.GetMouseLeft(AppFrame::InputState::Pressed) && _threadHolder == nullptr) {
		if (_myCard != nullptr && !_settMyCard) {
			_threadHolder = std::make_unique<PostThread>(_myCard);
			_threadHolder->ThreadStart();
			_settMyCard = true;
		}
		if (_opponentCard != nullptr && !_setOpponentCard) {
			_threadHolder = std::make_unique<PostThread>(_opponentCard);
			_threadHolder->ThreadStart();
			_setOpponentCard = true;
		}
	}
	*/
}

void BattleField::Render()
{
	auto renderCard = [](AppFrame::VECTOR2<int> position, std::unique_ptr<CardObject>& card) {
		/*
		DrawRotaGraph(position.x, position.y-80, 0.8f, 0.0f, card->GetImage(), true);
		DrawRotaGraph(position.x, position.y, 0.8f, 0.0f, card->GetFrameImage(), true);

		DrawString(position.x - 130, position.y - 180, card->GetCardName().c_str(), AppFrame::Color::Red);
		DrawString(position.x - 130, position.y - 20 + 25, card->GetCardText().c_str(), AppFrame::Color::Red);
		*/
		DrawRotaGraph(position.x, position.y, 0.8f, 0.0f, card->GetScreen(), true);
		if (card->GetAttack() != -1) {
			DrawString(position.x - 80, position.y + 160, std::to_string(card->GetAttack()).c_str(), AppFrame::Color::Red);
			DrawString(position.x + 60, position.y + 160, std::to_string(card->GetDefense()).c_str(), AppFrame::Color::Red);
		}
	};

	if (_myCard != nullptr) {
		if (_myCard->GetCardName() != "") {
			renderCard(MyPosition, _myCard);
		}

	}
	if (_opponentCard != nullptr) {
		if (_opponentCard->GetCardName() != "") {
			renderCard(OpponentPosition, _opponentCard);
		}
	}

	std::string myResult{ "" };
	std::string opponentResult{ "" };
	if (_settMyCard && _setOpponentCard) {
		int myPower = _myCard->GetAttack() + _myCard->GetDefense();
		int opponentPower = _opponentCard->GetAttack() + _opponentCard->GetDefense();
		if (myPower == opponentPower) {
			myResult = "ˆø‚«•ª‚¯";
			opponentResult = "ˆø‚«•ª‚¯";
		}
		else if (myPower > opponentPower) {
			myResult = "Ÿ‚¿I";
			opponentResult = "•‰‚¯";
		}
		else {
			myResult = "•‰‚¯";
			opponentResult = "Ÿ‚¿";
		}
		DrawStringToHandle(MyPosition.x, MyPosition.y, myResult.c_str(), AppFrame::Color::Yellow, _font);
		DrawStringToHandle(OpponentPosition.x, OpponentPosition.y, opponentResult.c_str(), AppFrame::Color::Yellow, _font);
	}
}

void BattleField::Debug()
{
}

void BattleField::SetMyArea(CardData card)
{
	_myCard = _modeInGame.GetCardFactory()->CreateCard(card);
}

void BattleField::SetOpponentArea(CardData card)
{
	_opponentCard = _modeInGame.GetCardFactory()->CreateCard(card);
}
