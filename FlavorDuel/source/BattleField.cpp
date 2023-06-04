#include "BattleField.h"
#include "CardObject.h"
#include "PostData.h"
#include "ModeInGame.h"
#include "CardFactory.h"
using namespace Flavor;

namespace {
	AppFrame::VECTOR2<int> MyPosition = { 400,350 };
	AppFrame::VECTOR2<int> OpponentPosition = { 750,300 };

	constexpr float JudgeConfirmTime = 5.0f;

	constexpr auto Font32Name = "GGothic32";
	constexpr auto Font16Name = "GGothic16";
}

BattleField::BattleField(ModeInGame& mode)
	:_modeInGame{ mode }
	, _myCard{ nullptr }
	, _opponentCard{ nullptr }
	, _threadHolder{ nullptr }
	, _confirm{ false }
	, _judgeCompleteTimer{ 0.0f }
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
	//���҃J�[�h���o���Ă��邩
	if (!(_myCard && _opponentCard)) {
		return;
	}
	//���҂̃J�[�h�ɍU���͂��ݒ肳��Ă��邩
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
	auto renderCard = [this](AppFrame::VECTOR2<int> position, std::unique_ptr<CardObject>& card) {
		DrawRotaGraph(position.x, position.y, 0.8f, 0.0f, card->GetScreen(), true);
		if (card->GetAttack() != -1) {
			DrawStringToHandle(position.x - 90, position.y + 150, std::to_string(card->GetAttack()).c_str(), AppFrame::Color::Black, _font);
			DrawStringToHandle(position.x + 50, position.y + 150, std::to_string(card->GetDefense()).c_str(), AppFrame::Color::Black, _font);
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
			myResult = "��������";
			opponentResult = "��������";
		}
		else if (myPower > opponentPower) {
			myResult = "�����I";
			opponentResult = "����";
		}
		else {
			myResult = "����";
			opponentResult = "����";
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
