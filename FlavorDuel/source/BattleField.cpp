#include "BattleField.h"
#include "CardObject.h"
#include "PostData.h"
#include "ModeInGame.h"
#include "CardFactory.h"
using namespace Flavor;

namespace {
	AppFrame::VECTOR2<int> MyPosition = { 400,350 };
	AppFrame::VECTOR2<int> OpponentPosition = { 750,300 };

	constexpr float JudgeConfirmTime = 2.0f;
}

BattleField::BattleField(ModeInGame& mode)
	:_modeInGame{ mode }
	, _myCard{ nullptr }
	, _opponentCard{ nullptr }
	, _threadHolder{ nullptr }
	, _confirm{ false }
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
	//両者カードを出しているか
	if (!(_myCard && _opponentCard)) {
		return;
	}
	//両者のカードに攻撃力が設定されているか
	int myPower = _myCard->GetAttack();
	int opponentPower = _opponentCard->GetAttack();
	if (myPower == -1 || opponentPower == -1) {
		return;
	}
	_JudgeCompleteTimer += _modeInGame.GetStepTime() * 0.001f;
	if (_JudgeCompleteTimer > JudgeConfirmTime) {
		_JudgeCompleteTimer = 0.0f;
		if (!_confirm) {
			_confirm = true;
			_modeInGame.SetJudgeConfirm();
		}
	}
}

void BattleField::Render()
{
	auto renderCard = [](AppFrame::VECTOR2<int> position, std::unique_ptr<CardObject>& card) {
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
	if (_myCard && _opponentCard) {
		int myPower = _myCard->GetAttack();
		int opponentPower = _opponentCard->GetAttack();

		if (myPower == -1 || opponentPower == -1) {
			return;
		}

		if (myPower == opponentPower) {
			myResult = "引き分け";
			opponentResult = "引き分け";
		}
		else if (myPower > opponentPower) {
			myResult = "勝ち！";
			opponentResult = "負け";
		}
		else {
			myResult = "負け";
			opponentResult = "勝ち";
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
