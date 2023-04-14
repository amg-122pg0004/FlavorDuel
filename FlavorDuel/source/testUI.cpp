#include "testUI.h"

namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 640,480 };
}

testUI::testUI() :AppFrame::UICanvas(CanvasSize)
{
	auto button1 = std::make_unique<AppFrame::UI::Button>();
	button1->SetPosition({ 580,380 });
	button1->SetAnchor(AppFrame::UIObjectBase::Anchor::Center);
	auto text1 = std::make_unique<AppFrame::UI::TextBox>("‹­‚³”»’è");
	button1->SetTextBox(std::move(text1));
	this->AddUIObject(std::move(button1));

	auto cardFrame = std::make_unique<AppFrame::UI::Image>("res/CardFrame.png");
	AppFrame::VECTOR2<int> halfSize = { static_cast<int>(static_cast<float>(CanvasSize.x) * 0.5f), static_cast<int>(static_cast<float>(CanvasSize.y) * 0.5f) };
	cardFrame->SetPosition(halfSize);
	cardFrame->SetAnchor(AppFrame::UIObjectBase::Anchor::Center);
	cardFrame->SetScale(0.8f);
	this->AddUIObject(std::move(cardFrame));

}

void testUI::Init()
{
	AppFrame::UICanvas::Init();
}

void testUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void testUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
}

void testUI::Render()
{
	AppFrame::UICanvas::Render();
}
