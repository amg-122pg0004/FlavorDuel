#include "MatchingUI.h"
#include "ModeMatching.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	constexpr AppFrame::VECTOR2<int> CancelButtonPosition = { 640,500 };
	constexpr AppFrame::VECTOR2<int> ImagePosition = { 640,300 };
	constexpr AppFrame::VECTOR2<int> MessageTextPosition = { 640,100 };

	constexpr auto loadingImagePath = "res/loading.png";
	constexpr auto GothicFont32 = "GGothic32";
	constexpr auto GothicFont16 = "GGothic16";
}

MatchingUI::MatchingUI(ModeMatching& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _mode{ mode }
{
	int smallFontHandle = AppFrame::FontServer::Find(GothicFont16);
	int fontHandle = AppFrame::FontServer::Find(GothicFont32);

	auto messageText = std::make_unique<AppFrame::UI::TextBox>("対戦相手を検索中");
	messageText->SetAnchor(Anchor::Center);
	messageText->SetPosition(MessageTextPosition);
	messageText->SetFont(fontHandle);
	messageText->SetTextColor(AppFrame::Color::Red);
	this->AddUIObject(std::move(messageText));

	auto stopMatchingButton = std::make_unique<AppFrame::UI::Button>();
	stopMatchingButton->SetAnchor(Anchor::Center);
	stopMatchingButton->SetPosition(CancelButtonPosition);
	auto stopText = std::make_unique<AppFrame::UI::TextBox>("中断");
	stopText->SetFont(fontHandle);
	stopMatchingButton->SetTextBox(std::move(stopText));
	auto stopfunction = [this]() {
		_mode.StopMatching();
	};
	stopMatchingButton->SetFunction(stopfunction);
	this->AddUIObject(std::move(stopMatchingButton));

	auto loadingImage = std::make_unique<AppFrame::UI::Image>(loadingImagePath);
	loadingImage->SetAnchor(Anchor::Center);
	loadingImage->SetPosition(ImagePosition);
	auto rotateUpdate = [this](AppFrame::UI::Image& image) {
		int rotIndex = 8 - std::ceil((_mode.GetModeTime() % 1600)/200);
		image.SetAngle(AppFrame::Math::TwoPi / 8.0f * rotIndex);//画像に合わせて1/8回転
	};
	loadingImage->SetUpdateFunction(rotateUpdate);
	loadingImage->SetNeedUpdate(true);
	this->AddUIObject(std::move(loadingImage));

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
