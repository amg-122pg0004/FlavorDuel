#include "TitleUI.h"
#include "ModeTitle.h"
using namespace Flavor;
namespace {
	AppFrame::VECTOR2<int> CanvasSize = { 1280,780 };
}

TitleUI::TitleUI(ModeTitle& mode):AppFrame::UICanvas(CanvasSize)
{
	auto userNameBox = std::make_unique<AppFrame::UI::EditableTextBox>();
	auto passwordBox = std::make_unique<AppFrame::UI::EditableTextBox>();

	auto loginButton = std::make_unique<AppFrame::UI::Button>();


	auto registerButton = std::make_unique<AppFrame::UI::Button>();
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	AppFrame::UICanvas::Init();
}

void TitleUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void TitleUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input,deltaSeconds);
}

void TitleUI::Render()
{
	AppFrame::UICanvas::Render();
}