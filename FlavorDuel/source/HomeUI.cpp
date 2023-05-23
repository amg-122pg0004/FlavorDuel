#include "HomeUI.h"
#include "PostData.h"
#include "UserDataStruct.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	AppFrame::VECTOR2<int> CanvasSize = { 1280,780 };

	AppFrame::VECTOR2<int> casualBattleButtonPosition = { 320,290 };
	AppFrame::VECTOR2<int> rankBattleButtonPosition = { 960,290 };
	AppFrame::VECTOR2<int> deckEditButtonPosition = { 320,600 };
	AppFrame::VECTOR2<int> shopButtonPosition = { 960,600 };
}

HomeUI::HomeUI()
	:AppFrame::UICanvas(CanvasSize)
{
	auto casualBattleButton = std::make_unique<AppFrame::UI::Button>();
	casualBattleButton->SetAnchor(Anchor::Center);
	casualBattleButton->SetPosition(casualBattleButtonPosition);
	auto casualText = std::make_unique<AppFrame::UI::TextBox>("カジュアル");
	casualBattleButton->SetTextBox(std::move(casualText));
	auto casualMatching = [&]() {
		auto app = AppFrame::ApplicationBase::GetInstance();
		_matchingThread.reset(new MatchingThread(app->GetAppData()->GetData<UserData>().id));
		_matchingThread->ThreadStart();
	};
	casualBattleButton->SetFunction(std::move(casualMatching));
	this->AddUIObject(std::move(casualBattleButton));

	auto rankBattleButton = std::make_unique<AppFrame::UI::Button>();
	rankBattleButton->SetAnchor(Anchor::Center);
	rankBattleButton->SetPosition(rankBattleButtonPosition);
	auto rankText = std::make_unique<AppFrame::UI::TextBox>("ランク");
	rankBattleButton->SetTextBox(std::move(rankText));
	auto rankMatching = []() {

	};
	rankBattleButton->SetFunction(std::move(rankMatching));
	this->AddUIObject(std::move(rankBattleButton));

	auto deckEditButton = std::make_unique<AppFrame::UI::Button>();
	deckEditButton->SetAnchor(Anchor::Center);
	deckEditButton->SetPosition(deckEditButtonPosition);
	auto deckEditText = std::make_unique<AppFrame::UI::TextBox>("デッキ編集");
	deckEditButton->SetTextBox(std::move(deckEditText));
	auto openDeckEdit = []() {

	};
	deckEditButton->SetFunction(std::move(openDeckEdit));
	this->AddUIObject(std::move(deckEditButton));

	auto shopButton = std::make_unique<AppFrame::UI::Button>();
	shopButton->SetAnchor(Anchor::Center);
	shopButton->SetPosition(shopButtonPosition);
	auto shopText = std::make_unique<AppFrame::UI::TextBox>("ショップ");
	shopButton->SetTextBox(std::move(shopText));
	auto openShop = []() {

	};
	shopButton->SetFunction(std::move(openShop));
	this->AddUIObject(std::move(shopButton));
}

HomeUI::~HomeUI()
{
}

void HomeUI::Init()
{
	AppFrame::UICanvas::Init();
}

void HomeUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void HomeUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
}

void HomeUI::Render()
{
	AppFrame::UICanvas::Render();
}
