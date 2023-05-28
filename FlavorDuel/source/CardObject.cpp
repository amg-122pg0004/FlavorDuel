#include "CardObject.h"
#include "BattleField.h"

namespace {
	constexpr auto CardFrame = "res/CardFrame.png";
	constexpr auto CardBack = "res/CardBack.png";
	constexpr float Scale = 0.38f;
	constexpr AppFrame::VECTOR2<int> NameOffset = { -75,-95 };
	constexpr AppFrame::VECTOR2<int> TextOffset = { -75,0 };

	constexpr AppFrame::VECTOR2<int> ClickCollisionSize = { 150,180 };
}

namespace Flavor {
	CardObject::CardObject() :_selected{ false }, _attack{ -1 }, _defense{ -1 }, _tips{ "" }
	{
		_frameCG = AppFrame::ImageServer::LoadGraph(CardFrame);
		_aabb = { {0,0},{0,0} };
	}

	CardObject::~CardObject() {

	}

	void CardObject::Init() {
		this->SetScale({ Scale, Scale, Scale });
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
		DrawRotaGraph(positionX, positionY, scale, 0.0f, _frameCG, true);

		DrawString(positionX + NameOffset.x, positionY + NameOffset.y, _cardName.c_str(), AppFrame::Color::Red);

		DrawString(positionX + TextOffset.x, positionY + TextOffset.y, _cardText.c_str(), AppFrame::Color::Red);
	}

	void CardObject::Debug() {

	}
}
