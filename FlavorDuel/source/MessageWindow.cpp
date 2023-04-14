#include "MessageWindow.h"
namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 320,80 };
	constexpr auto MessageBalloonPath = "res/TextBalloon2.png";

}

using namespace Flavor;

Flavor::MessageWindow::MessageWindow(std::string message)
	:AppFrame::UICanvas(CanvasSize)
{
	auto cg = std::make_unique<AppFrame::UI::Image>(MessageBalloonPath);
	this->AddUIObject(std::move(cg));

	int messageWidth = GetDrawStringWidth(message.c_str(), strlen(message.c_str()));

	int lineNumber = std::ceil(static_cast<float>(messageWidth) / static_cast<float>(CanvasSize.x));
	int oneLineCharNumber = std::ceil(static_cast<float>(message.size()) / static_cast<float>(lineNumber));
	int countByte{ 0 };
	for (int i = 0; i < static_cast<int>(message.size());) {
		int checkByte = AppFrame::ShiftJISChecker::Check(message.at(i));
		countByte += checkByte;
		if (countByte > oneLineCharNumber) {
			message.insert(i, "\n");
			countByte = 0;
		}
		i += checkByte;
	}

	auto text = std::make_unique<AppFrame::UI::TextBox>(message);
	text->SetPosition({ CanvasSize.x / 2,CanvasSize.y / 2 - 10 });
	text->SetAnchor(AppFrame::UIObjectBase::Anchor::Center);
	this->AddUIObject(std::move(text));
}

void Flavor::MessageWindow::Init()
{
	AppFrame::UICanvas::Init();
}

void Flavor::MessageWindow::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void Flavor::MessageWindow::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
}

void Flavor::MessageWindow::Render()
{
	AppFrame::UICanvas::Render();
}
