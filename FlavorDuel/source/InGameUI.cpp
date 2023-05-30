#include "InGameUI.h"
#include "ModeInGame.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };

	constexpr AppFrame::VECTOR2<int> MyWinNumberPosition = { 50,50 };
	constexpr AppFrame::VECTOR2<int> OpponentWinNumberPosition = { 50,630 };
}

InGameUI::InGameUI(ModeInGame& mode)
	:AppFrame::UICanvas(CanvasSize), _modeInGame{ mode }
{

	auto myWinNumberText = std::make_unique<AppFrame::UI::TextBox>("");
	myWinNumberText->SetPosition(MyWinNumberPosition);
	auto getMyWinNumber = [this]() {
		return std::to_string(_modeInGame.GetPlayerData().win);
	};
	myWinNumberText->SetBindFunction(getMyWinNumber);
	this->AddUIObject(std::move(myWinNumberText));

	auto opponentWinNumberText = std::make_unique<AppFrame::UI::TextBox>("");
	opponentWinNumberText->SetPosition(OpponentWinNumberPosition);
	auto getOpponentWinNumber = [this]() {
		return std::to_string(_modeInGame.GetOpponentData().win);
	};
	opponentWinNumberText->SetBindFunction(getOpponentWinNumber);
	this->AddUIObject(std::move(opponentWinNumberText));
}

InGameUI::~InGameUI()
{

}

void InGameUI::Init()
{
	UICanvas::Init();
}

void InGameUI::Terminate()
{
	UICanvas::Terminate();
}

void InGameUI::Update(InputManager& input, float deltaSeconds)
{
	UICanvas::Update(input, deltaSeconds);
}

void InGameUI::Render()
{
	UICanvas::Render();
}
