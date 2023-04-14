#include "MessageLog.h"

namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 320,720 };
	constexpr auto MessageBalloonPath = "res/TextBalloon.png";
}

using namespace Flavor;
MessageLog::MessageLog()
	:AppFrame::UICanvas(CanvasSize)
{
	this->SetNeedUpdate(true);
	this->SetName("MessageLog");
}

void MessageLog::Init()
{
}

void MessageLog::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void MessageLog::Update(InputManager& input, float deltaSeconds)
{

	int childNumber = static_cast<int>(this->GetChildCanvas().size());
	for (int i = 0; i < childNumber; ++i) {
		GetChildCanvas().at(i)->SetPosition({ 1280 - CanvasSize.x,i * 80, });
	}
	AppFrame::UICanvas::Update(input, deltaSeconds);
}

void MessageLog::Render()
{
	AppFrame::UICanvas::Render();
}
