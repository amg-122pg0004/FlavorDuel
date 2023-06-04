#include "HomeUI.h"
#include <sstream>
#include "PostData.h"
#include "UserDataStruct.h"
#include "ModeHome.h"

namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	constexpr AppFrame::VECTOR2<int> ButtonSize = { 200,100 };

	constexpr AppFrame::VECTOR2<int> casualBattleButtonPosition = { 320,200 };
	constexpr AppFrame::VECTOR2<int> rankBattleButtonPosition = { 960,200 };
	constexpr AppFrame::VECTOR2<int> deckEditButtonPosition = { 320,520 };
	constexpr AppFrame::VECTOR2<int> shopButtonPosition = { 960,520 };

	constexpr int TopBarHeight = 20;

	constexpr auto BackGroundImagePath = "res/background.png";
	constexpr auto GothicFont32 = "GGothic32";
	constexpr auto GothicFont16 = "GGothic16";
}

HomeUI::HomeUI(ModeHome& home)
	:AppFrame::UICanvas(CanvasSize)
	, _modeHome{ home }
{
	//背景画像
	auto backgroundImage = std::make_unique<AppFrame::UI::Image>(BackGroundImagePath);
	this->AddUIObject(std::move(backgroundImage));

	auto userData = AppFrame::ApplicationBase::GetInstance()->GetAppData()->GetData<UserData>();
	
	int fontHandle = AppFrame::FontServer::Find(GothicFont32);
	int smallFontHandle = AppFrame::FontServer::Find(GothicFont16);
	//画面上部のユーザー情報
	auto topBar = std::make_unique<AppFrame::UI::Box>();
	topBar->SetSize({ CanvasSize.x, TopBarHeight });
	topBar->SetColor(AppFrame::Color::Black);
	this->AddUIObject(std::move(topBar));
	std::stringstream topBatText;
	topBatText << "ユーザーID:" << userData.id << "　レベル:" << userData.level << "　所持金:" << userData.money;
	auto idText = std::make_unique<AppFrame::UI::TextBox>(topBatText.str());
	idText->SetTextColor(AppFrame::Color::White);
	idText->SetFont(smallFontHandle);
	this->AddUIObject(std::move(idText));
	//カジュアルマッチ検索ボタン
	auto casualBattleButton = std::make_unique<AppFrame::UI::Button>();
	casualBattleButton->SetAnchor(Anchor::Center);
	casualBattleButton->SetPosition(casualBattleButtonPosition);
	casualBattleButton->SetSize(ButtonSize);
	auto casualText = std::make_unique<AppFrame::UI::TextBox>("カジュアル");
	casualText->SetFont(fontHandle);
	casualText->SetTextColor(AppFrame::Color::Black);
	casualBattleButton->SetTextBox(std::move(casualText));
	auto casualMatching = [this]() {
		_modeHome.OpenMatching();
	};
	casualBattleButton->SetFunction(std::move(casualMatching));
	this->AddUIObject(std::move(casualBattleButton));
	//ランクマッチ検索ボタン
	auto rankBattleButton = std::make_unique<AppFrame::UI::Button>();
	rankBattleButton->SetAnchor(Anchor::Center);
	rankBattleButton->SetSize(ButtonSize);
	rankBattleButton->SetPosition(rankBattleButtonPosition);
	auto rankText = std::make_unique<AppFrame::UI::TextBox>("ランク");
	rankText->SetTextColor(AppFrame::Color::Black);
	rankText->SetFont(fontHandle);
	rankBattleButton->SetTextBox(std::move(rankText));
	auto rankMatching = [this]() {
		_modeHome.OpenMatching();
	};
	rankBattleButton->SetFunction(std::move(rankMatching));
	this->AddUIObject(std::move(rankBattleButton));
	//デッキ編集ボタン
	auto deckEditButton = std::make_unique<AppFrame::UI::Button>();
	deckEditButton->SetAnchor(Anchor::Center);
	deckEditButton->SetSize(ButtonSize);
	deckEditButton->SetPosition(deckEditButtonPosition);
	auto deckEditText = std::make_unique<AppFrame::UI::TextBox>("デッキ編集");
	deckEditText->SetTextColor(AppFrame::Color::Black);
	deckEditText->SetFont(fontHandle);
	deckEditButton->SetTextBox(std::move(deckEditText));
	auto openDeckEdit = [this]() {
		_modeHome.ChangeModeDeckEdit();
	};
	deckEditButton->SetFunction(std::move(openDeckEdit));
	this->AddUIObject(std::move(deckEditButton));
	//ショップボタン
	auto shopButton = std::make_unique<AppFrame::UI::Button>();
	shopButton->SetAnchor(Anchor::Center);
	shopButton->SetSize(ButtonSize);
	shopButton->SetPosition(shopButtonPosition);
	auto shopText = std::make_unique<AppFrame::UI::TextBox>("ショップ");
	shopText->SetTextColor(AppFrame::Color::Black);
	shopText->SetFont(fontHandle);
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
