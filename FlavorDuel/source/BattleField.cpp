#include "BattleField.h"
#include "CardObject.h"
#include "PostData.h"
#include "ModeInGame.h"
#include "CardFactory.h"
using namespace Flavor;

namespace {
	AppFrame::VECTOR2<int> MyPosition = { 400,350 };
	AppFrame::VECTOR2<int> OpponentPosition = { 750,300 };
	AppFrame::VECTOR2<int> MyResultPosition = { 350,70 };
	AppFrame::VECTOR2<int> OpponentResultPosition = { 700,70 };

	constexpr float JudgeConfirmTime = 5.0f;

	constexpr auto Font32Name = "GGothic32";
	constexpr auto Font16Name = "GGothic16";
	constexpr float RandomInterval = 0.2f;
}

BattleField::BattleField(ModeInGame& mode)
	:_modeInGame{ mode }
	, _myCard{ nullptr }
	, _opponentCard{ nullptr }
	, _threadHolder{ nullptr }
	, _confirm{ false }
	, _judgeCompleteTimer{ 0.0f }
	, _myRandom{ 0 }
	, _opponentRandom{ 0 }
	, _randomTimer{ 0.0f }
{
	_font = AppFrame::FontServer::Find(Font32Name);
	_fontSmall = AppFrame::FontServer::Find(Font16Name);
}

BattleField::~BattleField()
{
}

void BattleField::Init()
{

}

void BattleField::Terminate()
{
}

void BattleField::Update(InputManager& input)
{
	_randomTimer += _modeInGame.GetStepTime() * 0.001f;
	if (_randomTimer > RandomInterval) {
		_randomTimer = 0.0f;
		_myRandom = AppFrame::Random::GetBtetweenNumbers(100, 999);
		_opponentRandom = AppFrame::Random::GetBtetweenNumbers(100, 999);
	}

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
	_judgeCompleteTimer += _modeInGame.GetStepTime() * 0.001f;
	if (_judgeCompleteTimer > JudgeConfirmTime) {
		_judgeCompleteTimer = 0.0f;
		if (!_confirm) {
			_confirm = true;
			_modeInGame.SetJudgeConfirm();
		}
	}
}

void BattleField::Render()
{
	auto renderCard = [this](AppFrame::VECTOR2<int> position, std::unique_ptr<CardObject>& card, int random) {
		DrawRotaGraph(position.x, position.y, 0.8f, 0.0f, card->GetScreen(), true);
		std::string drawAttack{std::to_string(random)};
		std::string drawDefence{std::to_string(random)};
		auto drawColor{ AppFrame::Color::Gray};
		if (card->GetAttack() != -1) {
			drawAttack = std::to_string(card->GetAttack()).c_str();
			drawDefence = std::to_string(card->GetDefense()).c_str();
			drawColor = AppFrame::Color::Black;
		}
		DrawStringToHandle(position.x - 90, position.y + 150, drawAttack.c_str(), drawColor, _font);
		DrawStringToHandle(position.x + 50, position.y + 150, drawDefence.c_str(), drawColor, _font);
	};

	if (_myCard != nullptr) {
		if (_myCard->GetCardName() != "") {
			renderCard(MyPosition, _myCard, _myRandom);
		}

	}
	if (_opponentCard != nullptr) {
		if (_opponentCard->GetCardName() != "") {
			renderCard(OpponentPosition, _opponentCard, _opponentRandom);
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
		DrawStringToHandle(MyResultPosition.x + 2, MyResultPosition.y + 2, myResult.c_str(), AppFrame::Color::Black, _font);
		DrawStringToHandle(MyResultPosition.x, MyResultPosition.y, myResult.c_str(), AppFrame::Color::Yellow, _font);
		DrawStringToHandle(OpponentResultPosition.x + 2, OpponentResultPosition.y + 2, opponentResult.c_str(), AppFrame::Color::Black, _font);
		DrawStringToHandle(OpponentResultPosition.x, OpponentResultPosition.y, opponentResult.c_str(), AppFrame::Color::Yellow, _font);
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
