#include "CardObject.h"
#include "BattleField.h"
#include "StringFitting.h"

namespace {
	constexpr auto CardFrame = "res/CardFrame.png";
	constexpr auto CardBack = "res/CardBack.png";
	constexpr float Scale = 0.38f;
	constexpr AppFrame::VECTOR2<int> NameOffset = { -75,-95 };
	constexpr AppFrame::VECTOR2<int> TextOffset = { -75,0 };
	constexpr AppFrame::VECTOR2<int> ImageOffset = { 20,45 };

	constexpr AppFrame::VECTOR2<int> ClickCollisionSize = { 150,180 };
	constexpr AppFrame::VECTOR2<int> CardSize = { 400,500 };

	constexpr auto DartsFont = "GGothic32";
}

namespace Flavor {
	CardObject::CardObject() :_selected{ false }
	{
		_screen = MakeScreen(CardSize.x, CardSize.y);
		_frameCG = AppFrame::ImageServer::LoadGraph(CardFrame);
		_aabb = { {0,0},{0,0} };
	}

	CardObject::~CardObject() {
		DeleteGraph(_screen);
	}

	void CardObject::Init() {
		this->SetScale({ Scale, Scale, Scale });

		ReworkScreenImage();
	}

	void CardObject::Terminate() {

	}

	void CardObject::Update(InputManager& input) {
		int positionX{ static_cast<int>(this->GetPosition().x) };
		int positionY{ static_cast<int>(this->GetPosition().y) };
		_aabb.min.x = positionX - ClickCollisionSize.x / 2;
		_aabb.min.y = positionY - ClickCollisionSize.y / 2;
		_aabb.max.x = positionX + ClickCollisionSize.x / 2;
		_aabb.max.y = positionY + ClickCollisionSize.y / 2;

		if (input.GetMouseLeft(AppFrame::InputState::Pressed)) {

			auto selectPop = [&]() {
				VECTOR offset{ 0.0f,50.0f,0.0f };
				if (_selected) {
					offset = VScale(offset, -1);
				}
				this->SetPosition(VAdd(this->GetPosition(), offset));
			};

			if (AppFrame::CheckCollision::Within(_aabb, input.GetMouseXY())) {
				if (!_selected) {
					_selected = true;

					selectPop();
				}
			}
			else {
				if (_selected) {
					_selected = false;
					selectPop();
				}

			}
		}

	}

	void CardObject::Render() {
		int positionX{ static_cast<int>(this->GetPosition().x) };
		int positionY{ static_cast<int>(this->GetPosition().y) };
		double scale{ static_cast<double>(this->GetScale().x) };
		DrawRotaGraph(positionX, positionY, scale, 0.0f, _screen, true);
	}

	void CardObject::Debug() {

	}
	void CardObject::SetCardName(std::string name)
	{
		_data.name = name;
		ReworkScreenImage();
	}
	void CardObject::SetCardText(std::string text)
	{
		_data.flavorText = text;
		ReworkScreenImage();
	}
	void CardObject::ReworkScreenImage()
	{
		auto font = AppFrame::FontServer::Find(DartsFont);
		SetDrawScreen(_screen);
		DrawGraph(ImageOffset.x, ImageOffset.y, _cardCG, true);
		DrawGraph(0, 0, _frameCG, true);
		DrawStringToHandle(10, 10, _data.name.c_str(), AppFrame::Color::Black, font);

		std::string setText = StringFitting::InsertLineBreak(_data.flavorText, 18);
		DrawStringToHandle(10, 260, setText.c_str(), AppFrame::Color::Black, font);

		SetDrawScreen(DX_SCREEN_BACK);
	}
}
