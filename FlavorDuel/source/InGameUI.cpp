#include "InGameUI.h"
#include "ModeInGame.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };

	constexpr AppFrame::VECTOR2<int> OpponentWinNumberPosition = { 50,180 };
	constexpr AppFrame::VECTOR2<int> MyWinNumberPosition = { 50,500 };

	constexpr auto WinFramePath = "res/WinFrame.png";
	constexpr auto WinStarPath = "res/WinStar.png";
	constexpr int StarWidth = 40;

	constexpr auto GothicFont32 = "GGothic32";
}

InGameUI::InGameUI(ModeInGame& mode)
	:AppFrame::UICanvas(CanvasSize), _modeInGame{ mode }
{
	int font = AppFrame::FontServer::Find(GothicFont32);

	auto myWinNumber = std::make_unique<AppFrame::UI::Image>(WinFramePath);
	myWinNumber->SetPosition(MyWinNumberPosition);
	this->AddUIObject(std::move(myWinNumber));



	for (int i = 0; i < 3; ++i) {
		auto myWinStar = std::make_unique<AppFrame::UI::Image>(WinStarPath);
		myWinStar->SetPosition({ MyWinNumberPosition.x + StarWidth * i,MyWinNumberPosition.y });
		myWinStar->SetNeedUpdate(true);
		auto update = [this,i](AppFrame::UI::Image& image) {
			int win = _modeInGame.GetPlayerData().win;
			image.SetVisible(win > i);
		};
		myWinStar->SetUpdateFunction(update);
		this->AddUIObject(std::move(myWinStar));
	}

	auto opponentWinNumber = std::make_unique<AppFrame::UI::Image>(WinFramePath);
	opponentWinNumber->SetPosition(OpponentWinNumberPosition);
	this->AddUIObject(std::move(opponentWinNumber));

	for (int i = 0; i < 3; ++i) {
		auto opponentWinStar = std::make_unique<AppFrame::UI::Image>(WinStarPath);
		opponentWinStar->SetPosition({ OpponentWinNumberPosition.x + StarWidth * i,OpponentWinNumberPosition.y });
		opponentWinStar->SetNeedUpdate(true);
		auto update = [this, i](AppFrame::UI::Image& image) {
			int win = _modeInGame.GetOpponentData().win;
			image.SetVisible(win > i);
		};
		opponentWinStar->SetUpdateFunction(update);
		this->AddUIObject(std::move(opponentWinStar));
	}
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
