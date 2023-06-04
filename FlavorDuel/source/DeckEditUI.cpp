#include "DeckEditUI.h"
#include "ModeDeckEdit.h"
#include "CardImagePathLoader.h"
#include "CardFactory.h"
namespace {
	using namespace Flavor;
	using Anchor = AppFrame::UIObjectBase::Anchor;
	constexpr AppFrame::VECTOR2<int> CanvasSize = { 1280,720 };
	constexpr AppFrame::VECTOR2<int> CardListPosition = { 10,10 };
	constexpr AppFrame::VECTOR2<int> ApplyButtonPosition = { 700,650 };
	constexpr AppFrame::VECTOR2<int> HomeButtonPosition = { 1200,50 };
	constexpr AppFrame::VECTOR2<int> ScrollUpButtonPosition = { 200, 20 };
	constexpr AppFrame::VECTOR2<int> ScrollDownButtonPosition = { 200, 700 };

	constexpr int CardListSpace = 100;
	constexpr float CardListScale = 0.5f;

	constexpr AppFrame::VECTOR2<int> ListButtonSize = { 175,100 };
	constexpr AppFrame::VECTOR2<int> ApplyButtonSize = { 80,60 };
	constexpr AppFrame::VECTOR2<int> HomeButtonSize = { 80,60 };
	constexpr AppFrame::VECTOR2<int> ScrollButtonSize = { 25,35 };
	constexpr auto BackGroundImagePath = "res/background.png";
	constexpr auto fontName = "GGothic32";
}

DeckEditUI::DeckEditUI(ModeDeckEdit& mode)
	:AppFrame::UICanvas(CanvasSize)
	, _mode{ mode }
{
	int font = AppFrame::FontServer::Find(fontName);
	//背景画像
	auto backgroundImage = std::make_unique<AppFrame::UI::Image>(BackGroundImagePath);
	this->AddUIObject(std::move(backgroundImage));

	//一覧画像&ボタン
	std::vector<CardData> cards = _mode.GetCards();
	int cardCount{ 0 };
	for (auto&& card : cards) {
		//一覧画像
		std::string imagePath = _mode.GetCardFactory()->GetCardImagePathLoader()->GetPath(card.cg);
		auto image = std::make_unique<AppFrame::UI::Image>(imagePath);
		auto setPosition = CardListPosition;
		image->SetPosition({ setPosition.x,setPosition.y + CardListSpace * cardCount });
		image->SetScale(CardListScale);
		auto scrollFunction = [this, setPosition, cardCount](AppFrame::UI::Image& self) {
			AppFrame::VECTOR2<int> myPosition = { setPosition.x, setPosition.y + CardListSpace * (cardCount - _cardListScrollIndex) };
			self.SetVisible(myPosition.y > 0 && myPosition.y < CanvasSize.y - CardListSpace);
			self.SetPosition(myPosition);
		};
		image->SetUpdateFunction(scrollFunction);
		image->SetNeedUpdate(true);
		image->SetTransparent(false);
		this->AddUIObject(std::move(image));
		//一覧画像に重ねるボタン
		auto button = std::make_unique<AppFrame::UI::Button>();
		button->SetPosition({ setPosition.x,setPosition.y + CardListSpace * cardCount });
		button->SetSize(ListButtonSize);
		button->SetFill(false);
		auto scrollButtonFunction = [this, setPosition, cardCount](AppFrame::UI::Button& self) {
			AppFrame::VECTOR2<int> myPosition = { setPosition.x, setPosition.y + CardListSpace * (cardCount - _cardListScrollIndex) };
			self.SetVisible(myPosition.y > 0 && myPosition.y < CanvasSize.y - CardListSpace);
			self.SetPosition(myPosition);
		};
		button->SetUpdateFunction(scrollButtonFunction);
		auto setEditCardFunction = [this, cardCount]() {
			_mode.SetEditCard(_mode.GetCards().at(cardCount));
		};
		button->SetFunction(setEditCardFunction);
		this->AddUIObject(std::move(button));

		++cardCount;
	}

	//カード編集適用ボタン
	auto applyButton = std::make_unique<AppFrame::UI::Button>();
	applyButton->SetAnchor(Anchor::Center);
	applyButton->SetPosition(ApplyButtonPosition);
	applyButton->SetSize(ApplyButtonSize);
	auto applyFunction = [this]() {
		_mode.ApplyEditData();
	};
	applyButton->SetFunction(applyFunction);
	auto applyText = std::make_unique<AppFrame::UI::TextBox>("適用");
	applyText->SetTextColor(AppFrame::Color::Black);
	applyText->SetFont(font);
	applyButton->SetTextBox(std::move(applyText));
	this->AddUIObject(std::move(applyButton));

	//ホーム画面に戻るボタン
	auto homeButton = std::make_unique<AppFrame::UI::Button>();
	homeButton->SetAnchor(Anchor::Center);
	homeButton->SetPosition(HomeButtonPosition);
	homeButton->SetSize(HomeButtonSize);
	auto backFunction = [this]() {
		_mode.ChangeModeHome();
	};
	homeButton->SetFunction(backFunction);
	auto backText = std::make_unique<AppFrame::UI::TextBox>("戻る");
	backText->SetTextColor(AppFrame::Color::Black);
	backText->SetFont(font);
	homeButton->SetTextBox(std::move(backText));
	this->AddUIObject(std::move(homeButton));

	//スクロール上
	auto scrollUpButton = std::make_unique<AppFrame::UI::Button>();
	scrollUpButton->SetAnchor(Anchor::Center);
	scrollUpButton->SetPosition(ScrollUpButtonPosition);
	scrollUpButton->SetSize(ScrollButtonSize);
	auto scrollUpFunction = [this]() {
		_cardListScrollIndex--;
		if (_cardListScrollIndex < 0) {
			_cardListScrollIndex = 0;
		}
	};
	scrollUpButton->SetFunction(scrollUpFunction);
	auto upArrowText = std::make_unique<AppFrame::UI::TextBox>("↑");
	upArrowText->SetTextColor(AppFrame::Color::Black);
	upArrowText->SetFont(font);
	scrollUpButton->SetTextBox(std::move(upArrowText));
	this->AddUIObject(std::move(scrollUpButton));

	//スクロール下
	auto scrollDownButton = std::make_unique<AppFrame::UI::Button>();
	scrollDownButton->SetAnchor(Anchor::Center);
	scrollDownButton->SetPosition(ScrollDownButtonPosition);
	scrollDownButton->SetSize(ScrollButtonSize);
	auto scrollDownFunction = [this]() {
		_cardListScrollIndex++;
		if (_cardListScrollIndex >= _mode.GetCards().size() - 7) {
			_cardListScrollIndex = _mode.GetCards().size() - 7;
		}
	};
	scrollDownButton->SetFunction(scrollDownFunction);
	auto downArrowText = std::make_unique<AppFrame::UI::TextBox>("↓");
	downArrowText->SetTextColor(AppFrame::Color::Black);
	downArrowText->SetFont(font);
	scrollDownButton->SetTextBox(std::move(downArrowText));
	this->AddUIObject(std::move(scrollDownButton));
}

DeckEditUI::~DeckEditUI()
{
}

void DeckEditUI::Init()
{
	AppFrame::UICanvas::Init();
}

void DeckEditUI::Terminate()
{
	AppFrame::UICanvas::Terminate();
}

void DeckEditUI::Update(InputManager& input, float deltaSeconds)
{
	AppFrame::UICanvas::Update(input, deltaSeconds);
}

void DeckEditUI::Render()
{
	AppFrame::UICanvas::Render();
}
