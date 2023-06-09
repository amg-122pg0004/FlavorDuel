#include "InGameUI.h"
#include "ModeInGame.h"
#include "StringFitting.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;

	constexpr AppFrame::VECTOR2<int> OpponentWinNumberPosition = { 50,180 };
	constexpr AppFrame::VECTOR2<int> MyWinNumberPosition = { 50,500 };
	constexpr AppFrame::VECTOR2<int> MessageWindowPosition = { 960,10 };
	constexpr AppFrame::VECTOR2<int> MessageTextPosition = { 965,15 };

	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	constexpr int StarWidth = 40;

	constexpr auto WinFramePath = "res/WinFrame.png";
	constexpr auto WinStarPath = "res/WinStar.png";
	constexpr auto MessageWindowPath = "res/MessageWindow.png";

	constexpr auto GothicFont32 = "GGothic32";
}

InGameUI::InGameUI(ModeInGame& mode)
	:AppFrame::UICanvas(CanvasSize), _modeInGame{ mode }
{
	int font = AppFrame::FontServer::Find(GothicFont32);

	//メッセージウィンドウ
	auto messageWindow = std::make_unique<AppFrame::UI::Image>(MessageWindowPath);
	messageWindow->SetPosition(MessageWindowPosition);
	this->AddUIObject(std::move(messageWindow));
	auto messageText = std::make_unique<AppFrame::UI::TextBox>("MessageWindowPath");
	messageText->SetPosition(MessageTextPosition);
	messageText->SetTextColor(AppFrame::Color::White);
	auto getMessage = [this]() {
		std::vector<std::string> message = _modeInGame.GetRoomData().messageLog;
		std::string result;
		for (auto&& line : message) {
			std::string setText = StringFitting::InsertLineBreak(line, 32);
			setText += "---------------------------------\n";
			result += setText;
		}
		return result;
	};
	messageText->SetBindFunction(getMessage);
	this->AddUIObject(std::move(messageText));

	//自分の勝利数表示
	auto myWinNumber = std::make_unique<AppFrame::UI::Image>(WinFramePath);
	myWinNumber->SetPosition(MyWinNumberPosition);
	this->AddUIObject(std::move(myWinNumber));
	for (int i = 0; i < 3; ++i) {
		auto myWinStar = std::make_unique<AppFrame::UI::Image>(WinStarPath);
		myWinStar->SetPosition({ MyWinNumberPosition.x + StarWidth * i,MyWinNumberPosition.y });
		myWinStar->SetNeedUpdate(true);
		auto update = [this, i](AppFrame::UI::Image& image) {
			int win = _modeInGame.GetPlayerData().win;
			image.SetVisible(win > i);
		};
		myWinStar->SetUpdateFunction(update);
		this->AddUIObject(std::move(myWinStar));
	}

	//相手の勝利数表示
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
