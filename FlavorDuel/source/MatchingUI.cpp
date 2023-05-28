#include "MatchingUI.h"
#include "ModeMatching.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	AppFrame::VECTOR2<int> CanvasSize = { 1280,780 };
	AppFrame::VECTOR2<int> CenterPosition = { 640,390 };
}

MatchingUI::MatchingUI(ModeMatching& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _mode{ mode }
{
	auto stopMatchingButton = std::make_unique<AppFrame::UI::Button>();
	stopMatchingButton->SetAnchor(Anchor::Center);
	stopMatchingButton->SetPosition(CenterPosition);
	auto stopText = std::make_unique<AppFrame::UI::TextBox>("’†’f");
	stopMatchingButton->SetTextBox(std::move(stopText));
	auto stopfunction = [this]() {
		_mode.StopMatching();
	};
	stopMatchingButton->SetFunction(stopfunction);

	this->AddUIObject(std::move(stopMatchingButton));
}

MatchingUI::~MatchingUI()
{
}

void MatchingUI::Init()
{
	UICanvas::Init();
}

void MatchingUI::Terminate()
{
	UICanvas::Terminate();
}

void MatchingUI::Update(InputManager& input, float deltaSeconds)
{
	UICanvas::Update(input, deltaSeconds);
}

void MatchingUI::Render()
{
	UICanvas::Render();
}
