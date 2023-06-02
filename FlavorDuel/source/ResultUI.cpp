#include "ResultUI.h"
#include "ModeResult.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	constexpr AppFrame::VECTOR2<int> EndButtonPosition = { 640,500 };
	constexpr AppFrame::VECTOR2<int> TextPosition = { 640,300 };
	constexpr auto GothicFont32 = "GGothic32";
}

ResultUI::ResultUI(ModeResult& mode, bool win)
	:AppFrame::UICanvas(CanvasSize)
	, _modeResult{ mode }
{

	int font = AppFrame::FontServer::Find(GothicFont32);

	std::string setText{"èüÇøÅI"};
	if (win) {
		setText = "ïâÇØÅI";
	}
	auto titleText = std::make_unique<AppFrame::UI::TextBox>(setText);
	titleText->SetAnchor(Anchor::Center);
	titleText->SetPosition(TextPosition);
	titleText->SetFont(font);
	titleText->SetDrawBox(true);
	titleText->SetBoxColor(AppFrame::Color::Black);
	this->AddUIObject(std::move(titleText));

	auto stopMatchingButton = std::make_unique<AppFrame::UI::Button>();
	stopMatchingButton->SetAnchor(Anchor::Center);
	stopMatchingButton->SetPosition(EndButtonPosition);
	auto stopText = std::make_unique<AppFrame::UI::TextBox>("èIóπ");
	stopText->SetFont(font);
	stopMatchingButton->SetTextBox(std::move(stopText));
	auto stopfunction = [this]() {
		_modeResult.ChangeModeHome();
	};
	stopMatchingButton->SetFunction(stopfunction);
	this->AddUIObject(std::move(stopMatchingButton));
}

ResultUI::~ResultUI()
{
}

void ResultUI::Init()
{
	UICanvas::Init();
}

void ResultUI::Terminate()
{
	UICanvas::Terminate();
}

void ResultUI::Update(InputManager& input, float deltaSeconds)
{
	UICanvas::Update(input, deltaSeconds);
}

void ResultUI::Render()
{
	UICanvas::Render();
}
