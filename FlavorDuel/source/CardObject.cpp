#include "CardObject.h"
#include "BattleField.h"

namespace {
	constexpr auto CardFrame = "res/CardFrame.png";
	constexpr auto CardBack = "res/CardBack.png";
	constexpr float Scale = 0.38f;
	constexpr AppFrame::VECTOR2<int> NameOffset = { -75,-95 };
	constexpr AppFrame::VECTOR2<int> TextOffset = { -75,0 };
	constexpr AppFrame::VECTOR2<int> ImageOffset = { 20,45 };

	constexpr AppFrame::VECTOR2<int> ClickCollisionSize = { 150,180 };
	constexpr AppFrame::VECTOR2<int> CardSize = { 400,500 };
	constexpr auto DartsFontPath = "res/font/GenshinGothic-monoB4S32.dft";
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

		auto font = AppFrame::FontServer::LoadFont(DartsFontPath);
		SetDrawScreen(_screen);
		DrawGraph(ImageOffset.x, ImageOffset.y, _cardCG, true);
		DrawGraph(0, 0, _frameCG, true);
		DrawStringToHandle(10, 10, _data.name.c_str(), AppFrame::Color::Black, font);
		//ìKãXâ¸çs
		int oneLineCharNumber = 18;
		int countByte{ 0 };
		std::vector<int> insertIndex;
		for (int i = 0; i < static_cast<int>(_data.flavorText.size());) {
			int checkByte = AppFrame::ShiftJISChecker::Check(_data.flavorText.at(i));
			countByte += checkByte;
			i += checkByte;
			if (countByte > oneLineCharNumber) {
				insertIndex.emplace_back(i);
				countByte = 0;
			}
		}
		std::string setText{  _data.flavorText };
		for (auto itr = insertIndex.rbegin(); itr != insertIndex.rend(); ++itr) {
			setText.insert((*itr), "\n");
		}
		DrawStringToHandle(10, 260, setText.c_str(), AppFrame::Color::Black, font);

		SetDrawScreen(DX_SCREEN_BACK);
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
		/*
		DrawRotaGraph(positionX + ImageOffset.x, positionY + ImageOffset.y, scale, 0.0f, _cardCG, true);
		DrawRotaGraph(positionX, positionY, scale, 0.0f, _frameCG, true);


		DrawString(positionX + NameOffset.x, positionY + NameOffset.y, _data.name.c_str(), AppFrame::Color::Red);

		DrawString(positionX + TextOffset.x, positionY + TextOffset.y, _data.flavorText.c_str(), AppFrame::Color::Red);
		*/
		DrawRotaGraph(positionX, positionY, scale, 0.0f, _screen, true);
	}

	void CardObject::Debug() {

	}
}
